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
void DoGraphClustering(const I& inputs, const std::string& name){
  //chinese whispers algorithm
  std::vector<sample_pair> edges;
  for (long i = 0; i < inputs.nr(); ++i){
    for (long j = 0; j<inputs.nr(); ++j){
      auto dist = length(subm(inputs, i, 0, 1, 2) - subm(inputs, j, 0, 1, 2));
      if (dist < 1)
        edges.push_back(sample_pair(i, j, dist));
    }
  }
  std::vector<unsigned long> clusters;
  const auto num_clusters = chinese_whispers(edges, clusters);
  std::cout << "Num clusters detected: " << num_clusters << std::endl;
  Clusters plot_clusters;
  for (long i = 0; i != inputs.nr(); i++){
    auto cluster_idx = clusters[i];
    plot_clusters[cluster_idx].first.push_back(inputs(i, 0));
    plot_clusters[cluster_idx].second.push_back(inputs(i, 1));
  }

  PlotClusters(plot_clusters, "Agglomerative clustering", name + "-aggl.png");
}
