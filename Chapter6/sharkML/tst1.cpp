
//https://www.shark-ml.org/sphinx_pages/build/html/rest_sources/tutorials/algorithms/pca.html?highlight=pca

#include <plotcpp_clone/plotcpp/plot.h>

#define SHARK_CV_VERBOSE 1
#include <shark/Algorithms/Trainers/LDA.h>
#include <shark/Algorithms/Trainers/PCA.h>
#include <shark/Data/Csv.h>
#include <shark/Data/Dataset.h>
#include <shark/Models/Kernels/GaussianRbfKernel.h>


#include <experimental/filesystem>
#include <iostream>
#include <unordered_map>

namespace fs = std::experimental::filesystem;

using namespace shark;


const std::vector<std::string> colors{"black", "red", "blue", "green", "cyan"};

using DataType = double;
using Coords = std::vector<DataType>;
using PointCoords = std::pair<Coords, Coords>;
using Clusters = std::unordered_map<size_t, PointCoords>;

const std::string data_file_name{"swissroll.dat"};
const std::string labels_file_name{"swissroll_labels.dat"};

void PlotClusters(const Clusters& clusters,
                  const std::string& name,
                  const std::string& file_name) {
  plotcpp::Plot plt(true);
  // plt.SetTerminal("qt");
  plt.SetTerminal("png");
  plt.SetOutput(file_name);
  plt.SetTitle(name);
  plt.SetXLabel("x");
  plt.SetYLabel("y");
  // plt.SetAutoscale();
  plt.GnuplotCommand("set size square");
  plt.GnuplotCommand("set grid");

  auto draw_state = plt.StartDraw2D<Coords::const_iterator>();
  for (const auto& cluster : clusters) {
    std::stringstream params;
    params << "lc rgb '" << colors[cluster.first] << "' pt 7";
    plt.AddDrawing(draw_state,
                   plotcpp::Points(
                       cluster.second.first.cbegin(), cluster.second.first.cend(),
                       cluster.second.second.cbegin(),
                       std::to_string(cluster.first) + " cls", params.str()));
  }

  plt.EndDraw2D(draw_state);
  plt.Flush();
}


void PCAReduction(const UnlabeledData<RealVector>& data,
                  const UnlabeledData<RealVector>& labels,
                  size_t target_dim)
{
  /*
  The PCA algorithm in the shark-ML lib. are implemented in the PCA class.
  */
  PCA pca(data);
  LinearModel<> encoder;
  //Objects of PCA class should be configured with the encoder function.
  pca.encoder(encoder, target_dim);
  //void 	encoder (LinearModel<> &model, std::size_t m=0)
  //the 1st parameeter is a reference to the linearmodel class.


  auto new_data = encoder(data);


  Clusters clusters;

  for (size_t i = 0; i < new_data.numberOfElements(); ++i) {
    auto x = new_data.element(i)[0];
    auto y = new_data.element(i)[1];
    auto label = static_cast<int>(labels.element(i)[0]);
    clusters[label].first.push_back(x);
    clusters[label].second.push_back(y);
  }

  PlotClusters(clusters, "PCA", "../results/pca-sharkml.png");
}


void LDAReduction(const UnlabeledData<RealVector>& data,
                  const UnlabeledData<RealVector>& labels,
                  size_t target_dim) {
  /*
  The LDA algorithms in the Shark-ML lib. are implemented in the LDA class.
  First, we have to train the algorithm with the train() method, which takes
  two parameters the first one is a reference to the object of the LinearClassifier class,
  while the second is the dataset reference. Notice that the LDA algorithm uses objects of 
  LinearClassifier because, in the Shark-ML library, LDA is used mostly for classfication.
  */
  LinearClassifier<> encoder;
  LDA lda;

  
  LabeledData<RealVector, unsigned int> dataset(
    labels.numberOfElements(), InputLabelPair<RealVector, unsigned int>(
                                    RealVector(data.element(0).size()), 0));
    /*
    Also, because this is a supervised algorithm, we should provide labels for the data.
    We can do this by initializing the LabeledData<RealVector, unsigned int> class object. In 
    the following example, we can see how to combine UnlabeledData<RealVector> datasets with the 
    labeled one. 
    */
    for (size_t i = 0; i < labels.numberOfElements(); ++i) {
      // labels should start from 0
      dataset.element(i).label = 
         static_cast<unsigned int>(labels.element(i)[0]) - 1;
      dataset.element(i).input = data.element(i);
    }
    lda.train(encoder, dataset);
    /*
    After the object of the LinearCLassifier class has been trained, we can use it
    for data classfication as the function object. Its call result is a new labeled dataset.
    For dimensioanlity reduction, we have to use the decision function for data transformation.

    This function can be retrived using the decisionFunction() method of the LinearClassifier class.
    The decision function object can be used to transform the input data into a new prediction that can
    be obtained with the LDA. After we have the new labels and projected data, we can use them to obtain
    dimensionality reduced data. In the following example, we only used one label, which corresponds to
    the one dimension of the projection so that we can visualize the result. This means we're performing
    dimensionality reduction for the only feature(component).
    */
    // project data
    auto new_labels = encoder(data);
    auto dc = encoder.decisionFunction();
    auto new_data = dc(data);

    Clusters clusters;
    for (size_t i = 0; i < new_data.numberOfElements(); ++i) {
      auto l = new_labels.element(i);
      auto x = new_data.element(i)[l];
      auto y = new_data.element(i)[l];
      auto label = static_cast<int>(labels.element(i)[0]);
      clusters[label].first.push_back(x);
      clusters[label].second.push_back(y);
    }


    PlotClusters(clusters, "LDA", "../results/lda-sharkml.png");
}


        int main(int argc, char** argv) {
          if (argc > 1) {
            auto data_dir = fs::path(argv[1]);
            auto data_file_path = data_dir / data_file_name;
            auto labels_file_path = data_dir / labels_file_name;
          
          if (fs::exists(data_file_path) && fs::exists(labels_file_path)) {
            UnlabeledData<RealVector> data;
            importCSV(data, data_file_path, ' ');

            UnlabeledData<RealVector> labels;
            importCSV(labels, labels_file_path);

            int target_dim = 2;
            PCAReduction(data, labels, target_dim);
            LDAReduction(data, labels, target_dim);


          } else {
            std::cerr << "Dataset file " << data_file_path << " missed\n";
          }} else {
            std::cerr << "Please provide path to the dataset directory\n";
          }
        }

