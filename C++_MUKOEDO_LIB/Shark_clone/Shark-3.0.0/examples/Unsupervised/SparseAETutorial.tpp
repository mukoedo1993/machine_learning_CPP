
//###begin<includes>
#include <shark/Data/Pgm.h> //for exporting the learned filters
#include <shark/Data/Csv.h>//for reading in the images as csv
#include <shark/Data/Statistics.h> //for normalization
#include <shark/ObjectiveFunctions/SparseAutoencoderError.h>//the error function performing the regularisation of the hidden neurons
#include <shark/Algorithms/GradientDescent/LBFGS.h>// the L-BFGS optimization algorithm
#include <shark/ObjectiveFunctions/Loss/SquaredLoss.h> // squared loss used for regression
#include <shark/ObjectiveFunctions/Regularizer.h> //L2 regulariziation
//###end<includes>
#include <shark/Core/Timer.h> //measures elapsed time

using namespace std;
using namespace shark;

// Image info. The images are stored as w*h vectors, so we cannot derive
// w and h from the data.
//###begin<data_generation>
const unsigned int numsamples = 10000; //number of generated patches
const unsigned int w = 512;//width of loaded image
const unsigned int h = 512;//height of loaded image
const unsigned int psize = 8;//size of a patch
//###end<data_generation>

// FFNet parameters
//###begin<ffnet>
const unsigned int numhidden = 25;
const double rho = 0.01; // Sparsity parameter
const double beta = 6.0; // Regularization parameter
const double lambda = 0.0002; // Weight decay paramater
//###end<ffnet>

// Optimizer parameters
//###begin<train>
const unsigned int maxIter = 400;
//###end<train>

//###begin<get_samples_function>
UnlabeledData<RealVector> getSamples()
//###end<get_samples_function>
{
	//###begin<data_generation>
	// Read images
	UnlabeledData<RealVector> images;
	importCSV(images, "data/images.csv");
	unsigned int n = images.numberOfElements(); // number of images
	//###end<data_generation>
	cout << "Found " << n << " images of size " << w << "x" << h << endl;

	// Create the samples at random
	// Important notes: Since the images are in csv format, the width and
	// height is hardcoded. Because width = height we only have one integer
	// distribution below.
	
	//###begin<data_generation>
	// Sample equal amount of patches per image
	size_t patchesPerImg = numsamples / n;
	typedef UnlabeledData<RealVector>::element_range::iterator ElRef;
	
	// Create patches
	vector<RealVector> patches;
	for (ElRef it = images.elements().begin(); it != images.elements().end(); ++it) {
		for (size_t i = 0; i < patchesPerImg; ++i) {
			// Upper left corner of image
			unsigned int ulx = Rng::discrete(0,w-psize-1);
			unsigned int uly = Rng::discrete(0,w-psize-1);
			// Transform 2d coordinate into 1d coordinate and get the sample
			unsigned int ul = ulx * h + uly;
			RealVector sample(psize * psize);
			const RealVector& img = *it;
			for (size_t j = 0; j < psize; ++j)
				for (size_t k = 0; k < psize; ++k)
					sample(j * psize + k) = img(ul + k + j * h);
			patches.push_back(sample);
		}
	}
	
	UnlabeledData<RealVector> samples = createDataFromRange(patches);
	//###end<data_generation>
	
	//###begin<normalization>
	// zero mean
	RealVector meanvec = mean(samples);
	samples = transform(samples, Shift(-meanvec));

	// Remove outliers outside of +/- 3 standard deviations
	// and normalize to [0.1, 0.9]
	RealVector pstd = 3 * sqrt(variance(samples));
	samples = transform(samples, TruncateAndRescale(-pstd, pstd, 0.1, 0.9));
	//###end<normalization>
	
	return samples;
}

void initializeFFNet(Autoencoder<LogisticNeuron, LogisticNeuron>& model){
	// Set the starting point for the optimizer. This is 0 for all bias
	// weights and in the interval [-r, r] for non-bias weights.
	double r = std::sqrt(6.0) / std::sqrt(model.numberOfHiddenNeurons() + model.inputSize() + 1.0);
	RealVector params(model.numberOfParameters(),0);
	//we use  here, that the weights of the layers are the first in the vectors
	std::size_t hiddenWeights = model.inputSize()+model.outputSize();
	hiddenWeights *= model.numberOfHiddenNeurons();
	for(std::size_t i = 0; i != hiddenWeights;++i){
		params(i) = Rng::uni(-r,r);
	}
	model.setParameterVector(params);
}

int main()
{
	// Random needs a seed
	Rng::seed(42);
	
	// Read the data
	//###begin<create_dataset>
	UnlabeledData<RealVector> samples = getSamples();
	RegressionDataset data(samples, samples);
	//###end<create_dataset>
	cout << "Generated : " << samples.numberOfElements() << " patches." << endl;
	

	// Prepare the sparse network error function
	//###begin<ffnet>
	Autoencoder<LogisticNeuron, LogisticNeuron> model;
	model.setStructure(psize * psize, numhidden);
	initializeFFNet(model);
	//###end<ffnet>
	//###begin<sparsity_error>
	SquaredLoss<RealVector> loss;
	SparseAutoencoderError error(data,&model, &loss, rho, beta);
	// Add weight regularization
	TwoNormRegularizer regularizer(error.numberOfVariables());
	error.setRegularizer(lambda,&regularizer);
	//###end<sparsity_error>

	cout << "Model has: " << model.numberOfParameters() << " params." << endl;
	cout << "Model has: " << model.numberOfHiddenNeurons() << "hidden neurons." << endl;
	cout << "Model has: " << model.inputSize() << " inputs." << endl;
	cout << "Model has: " << model.outputSize() << " outputs." << endl;

	// Train it.
	//###begin<train>
	LBFGS optimizer;
	optimizer.lineSearch().lineSearchType() = LineSearch::WolfeCubic;
	optimizer.init(error);
	//###end<train>
	Timer timer;
	//###begin<train>
	for (unsigned int i = 0; i < maxIter; ++i) {
		optimizer.step(error);
		cout << "Error: " << optimizer.solution().value << endl;
	}
	//###end<train>
	cout << "Elapsed time: " << timer.stop() << endl;
	cout << "Function evaluations: " << error.evaluationCounter() << endl;

	//###begin<export>
	exportFiltersToPGMGrid("features",model.encoderMatrix(),psize,psize);
	//###end<export>
}
