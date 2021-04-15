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
The Chinese Whispers algorithm is an algorithm to partition the nodes of weighted,
undirected graphs. It was described in the paper Chinese Whispers -- an efficient graph
clustering algorithm and its application to natural language processing problems by Chris
Biemann. This algorithm also does not use any unique graph theory methods but it uses the 
idea of using local contexts for clustering, so it can be classified as a density-based method.
*/

/*
In the dlib lib., the algorithm is implemented in the chinese_whispers() function, which takes the vector
of weighted graph edges and outputs the container with cluster indices for each of the vertices. For the performance
consideration, we limit the number of edges between dataset objects with a threshold on distance. Moreover, as with the
Newman algorithm, this one also determines the No. of resulting clusters by itself. The code can be seen in the following
snippet:
*/

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
  /*
  The chinese_whispers() function call filled the clusters object with cluster index
  values, which we can use to visualize the clustering result. Notice that we used 1 as the threshold
  for edge weights, and another threshold value can lead to another clustering result. 
  
  Also, edge weight values should be initialized according to a certain task.

  The edge was chosen only for demonstration purposes.
  */
  std::cout << "Num clusters detected: " << num_clusters << std::endl;
  Clusters plot_clusters;
  for (long i = 0; i != inputs.nr(); i++){
    auto cluster_idx = clusters[i];
    plot_clusters[cluster_idx].first.push_back(inputs(i, 0));
    plot_clusters[cluster_idx].second.push_back(inputs(i, 1));
  }

  PlotClusters(plot_clusters, "Agglomerative clustering", name + "-aggl.png");
}


//References: see the documents' directory.