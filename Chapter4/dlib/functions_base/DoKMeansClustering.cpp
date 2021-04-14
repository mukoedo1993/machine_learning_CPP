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
The Dlib library uses kernel functions as the distance functions for the k-means 
algorithm. An example of such a function is the radial function. As an initial step,  we define the required
types, as follows:
*/
template <typename I>
void DoKMeansClustering(const I& inputs,
                        size_t num_clusters,
                        const std::string& name){
      typedef matrix<double, 2, 1> sample_type;
      typedef radial_basis_kernel<sample_type> kernel_type;
    kcentroid<kernel_type> kc(kernel_type(0.1), 0.01, 8);
    /*
    Then, we initialize an object of the kkmeans type. Its constructor takes 
    
    */
    kkmeans<kernel_type> kmeans(kc);

    std::vector<sample_type> samples;
    samples.reserve(inputs.nr());
    for( long i = 0; i !=inputs.nr(); i++){
      samples.push_back(dlib::trans(dlib::subm(inputs, i, 0, 1, 2)));
    }


    std::vector<sample_type> initial_centers;
    pick_initial_centers(num_clusters, initial_centers, samples,
                        kmeans.get_kernel());

    kmeans.set_number_of_centers(num_clusters);
    kmeans.train(samples, initial_centers);


    std::vector<unsigned long> clusters;
    Clusters plot_clusters;
    for( long i = 0; i != inputs.nr(); i++) {
      auto cluster_idx = kmeans(samples[i]);
      plot_clusters[cluster_idx].first.push_back(inputs(i, 0));
      plot_clusters[cluster_idx].second.push_back(inputs(i, 1));
    }

    PlotClusters(plot_clusters, "K-Means", name + "-kmeans.png");
}
