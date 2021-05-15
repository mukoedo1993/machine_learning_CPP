#include <dlib/matrix.h>
#include <dlib/svm_thread.h>
#include <plotcpp_clone/plotcpp/plot.h>

#include <experimental/filesystem>
#include <iostream>
#include <map>

using namespace dlib;
namespace fs = std::experimental::filesystem;

const std::vector<std::string> data_names{"dataset0.csv", "dataset1.csv",
                                          "dataset2.csv", "dataset3.csv",
                                          "dataset4.csv"};

const std::vector<std::string> colors{"red", "green", "blue", "cyan", "black"};

using DataType = double;
using Coords = std::vector<DataType>;
using PointCoords = std::pair<Coords, Coords>;
using Classes = std::map<size_t, PointCoords>;

using SampleType = matrix<DataType, 2, 1>;
using Samples = std::vector<SampleType>;
using Labels = std::vector<DataType>;


void PlotClasses(const Classes& classes,
                 const std::string& name,
                 const std::string& file_name) {
      plotcpp::Plot plt(true);
      // plt.SetTerminal("qt");
      plt.SetTerminal("png");
      plt.SetOutput(file_name);
      plt.SetXLabel("x");
      plt.SetYLabel("y");
      plt.SetAutoscale();
      plt.GnuplotCommand("set size square");
      plt.GnuplotCommand("set grid");

      auto draw_state = plt.StartDraw2D<Coords::const_iterator>();
      for (const auto& cls : classes) {
          std::stringstream params;
          params << "lc rgb '" << colors[cls.first] << "' pt 7";
          plt.AddDrawing(draw_state,
                         plotcpp::Points(
                             cls.second.first.cbegin(), cls.second.first.cend(),
                             cls.second.second.cbegin(),
                             std::to_string(cls.first) + " cls", params.str()
                         ));

      }

      plt.EndDraw2D(draw_state);
      plt.Flush();
}



void KRRClassification(const Samples& samples,
                       const Labels& labels,
                       const Samples& test_samples,
                       const Labels& test_labels,
                       const std::string& name) {

using OVOtrainer = one_vs_one_trainer<any_trainer<SampleType>>;
using KernelType = radial_basis_kernel<SampleType>;

krr_trainer<KernelType> krr_trainer;
krr_trainer.set_kernel(KernelType(0.1));

OVOtrainer trainer;
trainer.set_trainer(krr_trainer);

one_vs_one_decision_function<OVOtrainer> df = trainer.train(samples, labels);

Classes classes;
DataType accuracy = 0;
for(size_t i = 0; i != test_samples.size(); i++) {
    auto vec = test_samples[i];
    auto class_idx = static_cast<size_t>(df(vec));
    if (static_cast<size_t>(test_labels[i]) == class_idx)
     ++accuracy;
    classes[class_idx].first.push_back(vec(0, 0));
    classes[class_idx].second.push_back(vec(1, 0));
    //https://github.com/PacktPublishing/Hands-On-Machine-Learning-with-CPP/blob/master/Chapter07/dlib/dlib-classify.cc
  }

  accuracy /= test_samples.size();

  PlotClasses(classes, "Kernel Ridge Regression " + std::to_string(accuracy),
              "../results/" + name + "-krr-dlib.png");
}


void SVMClassification(const Samples& samples,
                       const Labels& labels,
                       const Samples& test_samples,
                       const Labels& test_labels,
                       const std::string& name) {
      using OVOtrainer = one_vs_one_trainer<any_trainer<SampleType>>;
      using KernelType = radial_basis_kernel<SampleType>;


      svm_nu_trainer<KernelType> svm_trainer;
      svm_trainer.set_kernel(KernelType(0.1));

      OVOtrainer trainer;
      trainer.set_trainer(svm_trainer);

      one_vs_one_decision_function<OVOtrainer> df = trainer.train(samples, labels);

      Classes classes;
      DataType accuracy = 0;
      for (size_t i = 0; i !=test_samples.size(); i++) {
          auto vec = test_samples[i];
          auto class_idx = static_cast<size_t>(df(vec));
          // line 109
          // https://github.com/PacktPublishing/Hands-On-Machine-Learning-with-CPP/blob/master/Chapter07/dlib/dlib-classify.cc
      }
      

}                        
                       