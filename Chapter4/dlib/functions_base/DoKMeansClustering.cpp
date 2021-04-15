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
//https://en.wikipedia.org/wiki/K-means_clustering
template <typename I>
void DoKMeansClustering(const I& inputs,
                        size_t num_clusters,
                        const std::string& name){
      typedef matrix<double, 2, 1> sample_type;
      typedef radial_basis_kernel<sample_type> kernel_type;

    /*
    Then, we initialize an object of the kkmeans type. Its constructor takes 
    an object that will define cluster centroids as input parameters. We can use an object 
    of the kcentroid type for this purpose. Its constructor takes three parameters: the first one 
    is the object that defines the kernel (distance function), the second is the numerical accuaracy for the
    centroid estimation, and the third one is the upper limit on the runtime complexity (actually,
    the maximum number of dictionary vectors the kcentroid objects is allowed to use), as 
    illustrated in the following code snippet:
    */
    kcentroid<kernel_type> kc(kernel_type(0.1), 0.01, 8);
    kkmeans<kernel_type> kmeans(kc);




    std::vector<sample_type> samples;
    samples.reserve(inputs.nr());
    for( long i = 0; i !=inputs.nr(); i++){
      samples.push_back(dlib::trans(dlib::subm(inputs, i, 0, 1, 2)));
    }

    /*
    As a next step, we initialize cluster centers with the pick_initial_centers() function.
    This function takes the No. of clusters, the output container for center objects, the training data,
    and the distance function object as a parameters, as follows:
    */
    std::vector<sample_type> initial_centers;
    pick_initial_centers(num_clusters, initial_centers, samples,
                        kmeans.get_kernel());



    /*
    When initial centers are selected, we can use them for the kkmeans::trains()
    method to determine exact clusters, as follows:
    */
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

/*
We used the kmeans object as a functor to perform clustering on a single data item. The 
clustering result will be the cluster's index for the item. Then, we used cluster indices to
visualize the final clustering result, as illustrated in the following screenshot:
In the preceding screenshot, we can see how the k-means clustering algorithm 
implemented in the dlib library works on different artificial datasets.
*/