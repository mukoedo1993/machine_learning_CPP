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


/*
The Dlib lib. implements the agglomerative hierarchical (bottom-up)
clustering algorithm. The bottom_up_cluster() function implements this
algorithm. This function takes the matrix of distances between dataset
objects, the cluster indices container (as the output parameter), and the number 
of clusters as input parameters. Notice that it returns the container with cluster
indices in the order of distances provided in the matrix.
*/

template <typename I>
void DoHierarhicalClustering (const I& inputs,
                               size_t num_clusters,
                               const std::string& name) {
// agglomerative clustering algorithm
/*
In the following code example, we fill the distance matrix with pairwise Euclidean 
distance, between each pair of elements in the input dataset:
*/
matrix<double> dists(inputs.nr(), inputs.nr());
for ( long r = 0; r < dists.nr(); ++r){
    for ( long c = 0; c < dists.nc(); ++c){
        dists(r, c) = length(subm(inputs, r, 0, 1, 2) - subm(inputs, c, 0, 1, 2));
    }
  }
  std::vector<unsigned long> clusters;

  /*
  The bottom_up_cluster() function call filled the clusters object with cluster index values,
  which we can use to visualize the clustering result, as illustrated in the following result:
  In the preceding screenshot, we can see how the hierarchical clustering algo. implemented in the dlib
  lib. works on different artificial datasets.
  */
  bottom_up_cluster(dists, clusters, num_clusters);
  Clusters plot_clusters;
  for (long i = 0; i != inputs.nr(); i++){
      auto cluster_idx = clusters[i];
      plot_clusters[cluster_idx].first.push_back(inputs(i, 0));
      plot_clusters[cluster_idx].second.push_back(input(i, 1));
  }

  PlotClusters(plot_clusters, "Agglomerative clustering", name + "-aggl.png");
}
