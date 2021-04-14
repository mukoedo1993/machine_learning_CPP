#include <dlib/clustering.h>
#include <dlib/matrix.h>
#include <plotcpp_clone/plotcpp/plot.h>

#include <experimental/filesystem>
#include <iostream>
#include <unordered_map>
#include "PlotClusters.h"

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


template <typename I>
void DoHierarhicalClustering (const I& inputs,
                               size_t num_clusters,
                               const std::string& name) {
// agglomerative clustering algorithm
matrix<double> dists(inputs.nr(), inputs.nr());
for ( long r = 0; r < dists.nr(); ++r){
    for ( long c = 0; c < dists.nc(); ++c){
        dists(r, c) = length(subm(inputs, r, 0, 1, 2) - subm(inputs, c, 0, 1, 2));
    }
  }
  std::vector<unsigned long> clusters;
  bottom_up_cluster(dists, clusters, num_clusters);
  Clusters plot_clusters;
  for (long i = 0; i != inputs.nr(); i++){
      auto cluster_idx = clusters[i];
      plot_clusters[cluster_idx].first.push_back(inputs(i, 0));
      plot_clusters[cluster_idx].second.push_back(input(i, 1));
  }

  PlotClusters(plot_clusters, "Agglomerative clustering", name + "-aggl.png");
}
