#include <dlib/clustering.h>
#include <dlib/matrix.h>
#include <plotcpp_clone/plotcpp/plot.h>

#include <experimental/filesystem>
#include <iostream>
#include <unordered_map>
#include "PlotClusters.h"
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
/*
The spectral clustering algorithms in the dlib library is implemented in the
spectral_cluster function. It takes the distance function object, the training dataset, and the number of clusters as
parameters. As a result, it returns a container with cluster indices, which have the same ordering as the input data.
In the following sample, the object of the knn_kernel type is used as a distance function. You will find its implementation
in the samples provided with the book. This knn_kernel distance function object estimates the samples provided with teh book.
This knn_kernel distance function obejct estimates the first k-nearest neighbor(KNN) objects to the given one. These objects 
are determined with the KNN algorithm, which uses the Euclidean distance for the distance measure, as follows:  

typedef matrix<double, 2, 1> sample_type;
typedef knn_kernel<sample_type> kernel_type;


std::vector<sample_type> samples;

 std::vector<unsigned long> clusters = 
  spectral_cluster(kernel_type(samples, 15), samples, num_clusters );

*/
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

 /*
 The spectral_cluster() function can filled the clusters object with cluster index values, which we can use to visualize 
 the clustering result, as illustrated in the following screenshot:
 In the preceding screenshot, we can see how the spectral clustering algorithm implemented in the dlib library works on 
 different artificial datasets.
 */
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
