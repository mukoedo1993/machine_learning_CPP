#include <dlib/clustering.h>
#include <dlib/matrix.h>
#include <plotcpp_clone/plotcpp/plot.h>

#include <experimental/filesystem>
#include <iostream>
#include <unordered_map>
#include "PlotClusters.h"
/*
Implementation of this algorithm is based on the work
Modularity and community structure in networks. This algorithm is based on the
modularity matrix for a network or a graph and it is not based on particular graph
theory, but it has instead some similarities with spectral clustering, because it also 
uses eigenvectors.
The dlib library implements this algorithm in the newman_cluster() function, which takes a 
vector of weighted graph edges and outputs the container with cluster indices for each vertex. The 
initial step for using this algorithm is the definition of graph edges. In the following code sample, we make 
edges between almost every pair of dataset objects. Notice that we use pairs only with a distance greater than
a threshold (this was done for performance considerations).


Also, this algorithm does not require prior knowledge of the number of clusters. It can determine the No. of 
clusters by itself. The code can be seen in the following block:
*/
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
void DoGraphNewmanClustering(const I& inputs, const std::string& name) {
  std::vector<sample_pair> edges;
  for ( long i = 0; i < inputs.nr(); ++i){
    for (long j = 0; j < inputs.nr(); ++j){
      auto dist = length(subm(inputs, i, 0, 1, 2) - subm(inputs, j, 0, 1, 2));
      if (dist < 0.5)
       edges.push_back(sample_pair(i, j, dist));
    }
  }
  remove_duplicate_edges(edges);

  std::vector<unsigned long>clusters;
  const auto num_clusters = newman_cluster(edges,clusters);
  std::cout << "Num clusters detected" << num_clusters << std::endl;
  Clusters plot_clusters;
  for( long i = 0; i != inputs.nr(); i++){
    auto cluster_idx = clusters[i];
    plot_clusters[cluster_idx].first.push_back(inputs(i, 0));
    plot_clusters[cluster_idx].second.push_back(inputs(i, 1));
  }

  PlotClusters(plot_clusters, "Graph Newman clustering",
               name + "-graph-newman.png");

}
/*
The newman_cluster() function call filled the clusters object with cluster index values,
which we can use to visualize the clustering result. Notice that another approach for
edge weight calculation can lead to another clustering result. Also, edge weight values
should be initialized according to a certain task. The edge length was chosen only for demonstration
purposes.
*/

/*
In the preceding screenshot, we can see how the Newman clustering algorithm 
implemented in the dlib lib. works on different artificial datasets.
*/