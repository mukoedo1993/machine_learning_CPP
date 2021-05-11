
#include <plotcpp_clone/plotcpp/plot.h>


#define SHARK_CV_VERBOSE_1
#include <shark/Algorithms/KMeans.h>
#include <shark/Algorithms/NearestNeighbors/TreeNearestNeighbors.h>
#include <shark/Algorithms/Trainers/CSvmTrainer.h>
#include <shark/Algorithms/Trainers/LogisticRegression.h>
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

    PlotClasses(classes, "../results/kNN " + std::to_string(accuracy),
                name + "-knn-sharkml.png");
}


void LRClassification(const ClassificationDataset& train,
                      const ClassificationDataset& test,
                      const unsigned int num_classes,
                      const std::string& name){

     OneVersusOneClassifier<RealVector> ovo;
     const unsigned int pairs = num_classes * (num_classes - 1) / 2;
     std::vector<LinearClassifier<RealVector>> lr(pairs);
     // line 96
     // https://github.com/PacktPublishing/Hands-On-Machine-Learning-with-CPP/blob/master/Chapter07/sharkml/sharkml-classify.cc
}