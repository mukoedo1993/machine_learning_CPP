/*
The shark-ml library has a more low-level approach to
the multi-class classification problem. Logistic regression and SVM classifiers are implemented
as binary classifiers. The user therefore has to explicitly train N(N-1)/2 classifiers and configure the 
object of the OneVersusOneClassifier class to combine them in a multi-class classifer. The kNN algorithm is
a multi-class classifier by nature.
*/


#include <plotcpp_clone/plotcpp/plot.h>


#define SHARK_CV_VERBOSE_1
#include <shark/Algorithms/KMeans.h>
#include <shark/Algorithms/NearestNeighbors/TreeNearestNeighbors.h>
#include <shark/Algorithms/Trainers/CSvmTrainer.h>
#include <shark/Algorithms/Trainers/LogisticRegression.h>
#include <shark/Data/Csv.h>
#include <shark/Data/Dataset.h>
#include <shark/Models/Classifier.h>
#include <shark/Models/Kernels/GaussianRbfKernel.h>
#include <shark/Models/NearestNeighborModel.h>
#include <shark/Models/OneVersusOneClassifier.h>
#include <shark/Models/Trees/KDTree.h>
#include <shark/ObjectiveFunctions/Loss/ZeroOneLoss.h>

#include <experimental/filesystem>
#include <iostream>
#include <unordered_map>


namespace fs = std::experimental::filesystem;

using namespace shark;

const std::vector<std::string> data_names{"dataset0.csv", "dataset1.csv",
                                          "dataset2.csv", "dataset3.csv",
                                          "dataset4.csv"};

const std::vector<std::string> colors{"red", "green", "blue", "cyan", "black"};

using DataType = double;
using Coords = std::vector<DataType>;
using PointCoords = std::pair<Coords, Coords>;
using Classes = std::unordered_map<size_t, PointCoords>;

void PlotClasses(const Classes& classes,
                const std::string& name,
                const std::string& file_name) {
     plotcpp::Plot plt(true);
     // plt.SetTerminal("qt");
     plt.SetTerminal("png");
     plt.SetOutput(file_name);
     plt.SetTitle(name);
     plt.SetXLabel("x");
     plt.SetYLabel("y");
     plt.SetAutoscale();
     plt.GnuplotCommand("set grid");

     auto draw_state = plt.StartDraw2D<Coords::const_iterator>();
     for (const auto& cls : classes) {
         std::stringstream params;
         params << "lc rgb '" << colors[cls.first] << "' pt 7";
         plt.AddDrawing(
             draw_state,
             plotcpp::Points(cls.second.first.cbegin(), cls.second.first.cend(),
                            cls.second.second.cbegin(),
                            std::to_string(cls.first) + " cls", params.str()));
         

     }

     plt.EndDraw2D(draw_state);
     plt.Flush();
}



void KNNClassification(const ClassificationDataset& train,
                       const ClassificationDataset& test,
                       unsigned int num_classes,
                       const std::string& name) {
     KDTree<RealVector> tree(train.inputs());
     TreeNearestNeighbors<RealVector, unsigned int> nn_alg(train, &tree);
     const unsigned int k = 5;
     NearestNeighborModel<RealVector, unsigned int> knn(&nn_alg, k);

    // compute errors
    ZeroOneLoss<unsigned int> loss;
    Data<unsigned int> predictions = knn(test.inputs());
    double accuracy = 1. - loss.eval(test.labels(), predictions);

    Classes classes;
    for (std::size_t i = 0; i != test.numberOfElements(); i++) {
        auto cluster_idx = predictions.element(i);
        auto element = test.inputs().element(i);
        classes[cluster_idx].first.push_back(element(0));
        classes[cluster_idx].second.push_back(element(1));
    }

    PlotClasses(classes, "kNN " + std::to_string(accuracy),
                "../results/ " + name + "-knn-sharkml.png");
}

/*
The following example shows how to implement the multi-class classification with 
Shark-ML and the logistic regression algorithm. The following code snippet introduces
a function declaration for this kind of task:
*/
/*
Steps:
1: Firstly, we defined the ovo object of the OneVersusOneClassifier class, which encapsulates
the single multi-class classifier.
2: Then, we initialized all binary classifiers for the one-versus-one strategy and placed them 
in the lr container object of the
std::vector<LinearClassifier<RealVector>> type.
3: We then trained the set of binary classifiers with the trainer object of the LogisticRegression type
and put them into the lr container.
4: We then ran the training with nested cycles over all classes. Notice that the lr container holds the 
instances to perform the final classification.
The ovo_classifiers object contains the pointers to binary classifiers. These classifiers are configured in such a way that
each of them classifies a single class(cls1) as positive, and all other classes are treated as negative ( cls2 ).
5: We then used the ovo_classifiers object to populate the ovo object, using the addClass method.

Another important factor is how we separate the data needed for training a single binary classifier.
The shark-ML library has a particular function for this task called binarySubProblem, which takes the object of the 
ClassificationDataset type and splits it in a way that is suitable for binary classification, even if the original dataset
is a multi-class one. The second and the third argunments of this function are ther zero class label index and the one class label
index respectively.
*/
void LRClassification(const ClassificationDataset& train,
                      const ClassificationDataset& test,
                      unsigned int num_classes,
                      const std::string& name){

     OneVersusOneClassifier<RealVector> ovo;
     const unsigned int pairs = num_classes * (num_classes - 1) / 2;
     std::vector<LinearClassifier<RealVector>> lr(pairs);
     for (std::size_t n = 0, cls1 = 1; cls1 < num_classes; cls1++) {
         std::vector<OneVersusOneClassifier<RealVector>::binary_classifier_type*>
              ovo_classifiers;
              /*
              tricky part:
              OneVersusOneClassifier<RealVector>::binary_classifier_type is an alias of 
              AbstractModel<RealVector,unsigned int, RealVector> here.
              But, LinearClassifier<RealVector> is a derived class of AbstractModel.
              Here, it is a base-to-derived pointer.
              */
     for (std::size_t cls2 = 0; cls2 < cls1; cls2++, n++) {
         // get the binary subproblem
         ClassificationDataset binary_cls_data = 
              binarySubProblem(train, cls2, cls1);
        
         // train the binary machine
         LogisticRegression<RealVector> trainer;
         trainer.train(lr[n], binary_cls_data);
         ovo_classifiers.push_back(&lr[n]);
     }
     ovo.addClass(ovo_classifiers);
  }
  // compute errors
  /*
  After we trained all binary classifiers and configured the OneVersusOneClassifier object, we used it for
  model evaluation on a test set. This object
  */
  ZeroOneLoss<unsigned int> loss;
  Data<unsigned int> output = ovo(test.inputs());
  double accuracy = 1. - loss.eval(test.labels(), output);

  Classes classes;
  for (std::size_t i = 0; i != test.numberOfElements(); i++) {
      auto cluster_idx = output.element(i);
      auto element = test.inputs().element(i);
      classes[cluster_idx].first.push_back(element(0));
      classes[cluster_idx].second.push_back(element(1));
  }

  PlotClasses(classes, "Logitstic Regression " + std::to_string(accuracy),
             "../results/"  + name + "-logreg-sharkml.png");
    
}



void SVMClassifcation(const ClassificationDataset& train,
                      const ClassificationDataset& test,
                      unsigned int num_classes,
                      const std::string& name) {
    double c = 10.0;
    double gamma = 0.5;
    GaussianRbfKernel<> kernel(gamma);
    OneVersusOneClassifier<RealVector> ovo;
    const unsigned int pairs = num_classes * (num_classes - 1) / 2;
    std::vector<KernelClassifier<RealVector> > svm(pairs);
    for (std::size_t n = 0, cls1 = 1; cls1 < num_classes; cls1++) {
        std::vector<OneVersusOneClassifier<RealVector>::binary_classifier_type*>
            ovo_classifiers;
        for (std::size_t cls2 = 0; cls2 < cls1; cls2++, n++) {
            // get the binary subproblem
            ClassificationDataset binary_cls_data = 
                binarySubProblem(train, cls2, cls1);

            // train the binary machine
            CSvmTrainer<RealVector> trainer(&kernel, c, false);
            trainer.train(svm[n], binary_cls_data);
            ovo_classifiers.push_back(&svm[n]);
        }
        ovo.addClass(ovo_classifiers);
    }

    // compute errors
    ZeroOneLoss<unsigned int> loss;
    Data<unsigned int> output = ovo(test.inputs());
    double accuracy = 1. - loss.eval(test.labels(), output);

    Classes classes;
    for (std::size_t i = 0; i != test.numberOfElements(); i++) {
        auto cluster_idx = output.element(i);
        auto element = test.inputs().element(i);
        classes[cluster_idx].first.push_back(element(0));
        classes[cluster_idx].second.push_back(element(1));
    }

    PlotClasses(classes, "SVM " + std::to_string(accuracy),
               "../results/" + name + "-svm-sharkml.png");
}



int main(int argc, char** argv) {
    if (argc > 1) {
        auto base_dir = fs::path(argv[1]);
        for (const auto& dataset : data_names) {
            auto dataset_name = base_dir / dataset;
            if (fs::exists(dataset_name)) {
                ClassificationDataset data;
                importCSV(data, dataset_name, LabelPosition::LAST_COLUMN);
                data = selectInputFeatures(
                    data, std::vector<int>{1, 2});      // exclude index column
            

            const std::size_t num_samples = data.numberOfElements();
            const std::size_t num_features = dataDimension(data.inputs());
            const std::size_t num_classes = numberOfClasses(data.labels());


            std::cout << dataset << "\n"
                      << "Num samples: " << num_features
                      << " num features: " << num_features
                      << " num clusters: " << num_classes << std::endl;
            
            // split data set in the training and testing parts
            ClassificationDataset test_data = splitAtElement(data, 1200);

            // create data set for multiclass problem
            repartitionByClass(data);

            SVMClassifcation(data, test_data, num_classes, dataset);
            LRClassification(data, test_data, num_classes, dataset);
            KNNClassification(data, test_data, num_classes, dataset);
        } else {
            std::cerr << "Dataset file " << dataset_name << " missed\n";
        }
    }
 }else {
     std::cerr << "Please provide path to the datasets folder\n";
 }
}