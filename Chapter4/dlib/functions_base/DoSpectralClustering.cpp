#include <dlib/clustering.h>
#include <dlib/matrix.h>
#include <plotcpp_clone/plotcpp/plot.h>

#include <experimental/filesystem>
#include <iostream>
#include <unordered_map>
//This object is intended to represent an edge in an undirected graph which has data samples at its vertices.
// Therefore, it is the undirected version of ordered_sample_pair.


using namespace dlib;
namespace fs = std::experimental::filesystem;
using SampleType = dlib::matrix<double, 1, 1>;
using Samples = std::vector<SampleType>;

const std::vector<std::string> data_names{
    "dataset0.csv", "dataset1.csv",
    "dataset2.csv", "dataset3.csv",
    "dataset4.csv", "dataset5.csv"
};

const std::vector<std::string> colors{"black", "red", "blue", "green",
                "cyan", "yellow", "brown", "magenta"};

using DataType = double;
using Coords = std::vector<DataType>;
using PointCoords = std::pair<Coords, Coords>;
using Clusters = std::unordered_map<size_t, PointCoords>;

template <typename T>
struct knn_kernel {
  knn_kernel(const std::vector<T>& samples, unsigned long k)
    : samples_(&samples){
      find_k_nearest_neighbors(
        samples, [](const T& a, const T& b){ return dlib::length(a - b);}, k,
        edges_);
      std::sort(edges_.begin(), edges_.end(), order_by_index<sample_pair>);   
    }
    DataType/*using DataType = double*/ 
    operator() (const T& a, const T& b) const {
      auto idx1 = std::distance(samples_->begin(),
                               std::find(samples_->begin(), samples_->end(), a));
      auto idx2 = std::distance(samples->begin(),
                                std::find(samples_->begin(), samples_->end(), b));
      sample_pair value{idx1, idx2};
      auto edge = std::lower_bound(edges_.begin(), edges_.end(), value,
                                  order_by_index<sample_pair>);  

      if (edge != edges_.end() && !order_by_index<sample_pair>(value, *edge))
        return 1;
      else
        return 0;                      
    }
    std::vector<sample_pair> edges_;
    const std::vector<T>* samples_;
};

template <typename I>
void DoSpectralClustering(const I& inputs,
                          size_t num_clusters,
                          const std::string& name){

typedef matrix<double, 2, 1> sample_type;
typedef knn_kernel<sample_type> kernel_type;


std::vector<sample_type> samples;
samples.reserve(inputs.nr());
for ( long i = 0; i != inputs.nr(); ++i){
 samples.push_back(dlib::trans(dlib::subm(inputs, i, 0, 1, 2)));
 }


 std::vector<unsigned long> clusters = 
  spectral_cluster(kernel_type(samples, 15), samples, num_clusters );


  Clusters plot_clusters;
  for ( long i = 0; i != inputs.nr(); i++){
    auto cluster_idx = clusters[i];
    plot_clusters[cluster_idx].first.push_back(inputs(i, 0));
    plot_clusters[cluster_idx].second.push_back(inputs(i, 1));
  }


  PlotClusters(plot_clusters, "Spectral clustering", name + "-spectral.png");
}
