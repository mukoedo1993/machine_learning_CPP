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

void PlotClusters(const Clusters& clusters,
                 const std::string& name,
                 const std::string& file_name) {
    
    plotcpp::Plot plt;
    plt.SetTerminal("png");
    plt.SetOutput(file_name);
    plt.SetTitle(name);
    plt.SetXLabel("x");
    plt.SetYLabel("y");
    plt.SetAutoscale();
    plt.GnuplotCommand("set grid");

    auto draw_state = plt.StartDraw2D<Coords::const_iterator>();
    for (auto& cluster : clusters) {
        std::stringstream params;
        params << "lc rgb '" << colors[cluster.first] << "'pt 7";
        plt.AddDrawing(draw_state,
                        plotcpp::Points(
                        cluster.second.first.begin(), cluster.second.first.end(),
                        cluster.second.second.begin(),
                        std::to_string(cluster.first) + " cls", params.str()));    
                        
    }
    
    plt.EndDraw2D(draw_state);
    plt.Flush();
}


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
      plot_clusters[cluster_idx].second.push_back(inputs(i, 1));
  }

  PlotClusters(plot_clusters, "Agglomerative clustering", "../results/" + name + "-aggl.png");
}

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
        /*!
        requires
            - is_ordered_by_index(edges) == true
        ensures
            - This function implements the graph clustering algorithm described in the
              paper: Chinese Whispers - an Efficient Graph Clustering Algorithm and its
              Application to Natural Language Processing Problems by Chris Biemann.
            - Interprets edges as a directed graph.  That is, it contains the edges on the
              said graph and the ordered_sample_pair::distance() values define the edge
              weights (larger values indicating a stronger edge connection between the
              nodes).  If an edge has a distance() value of infinity then it is considered
              a "must link" edge.
            - returns the number of clusters found.
            - #labels.size() == max_index_plus_one(edges)
            - for all valid i:
                - #labels[i] == the cluster ID of the node with index i in the graph.  
                - 0 <= #labels[i] < the number of clusters found
                  (i.e. cluster IDs are assigned contiguously and start at 0) 
            - Duplicate edges are interpreted as if there had been just one edge with a
              distance value equal to the sum of all the duplicate edge's distance values.
            - The algorithm performs exactly num_iterations passes over the graph before
              terminating.
    !*/

  std::cout << "Num clusters detected: " << num_clusters << std::endl;
  Clusters plot_clusters;
  for (long i = 0; i != inputs.nr(); i++){
    auto cluster_idx = clusters[i];
    plot_clusters[cluster_idx].first.push_back(inputs(i, 0));
    plot_clusters[cluster_idx].second.push_back(inputs(i, 1));
  }

  PlotClusters(plot_clusters, "Graph clustering", "../results/" + name + "-aggl.png");
}

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
              "../results/" +  name + "-graph-newman.png");

}


template <typename I>
void DoKMeansClustering(const I& inputs,
                        size_t num_clusters,
                        const std::string& name){
      typedef matrix<double, 2, 1>sample_type;
      typedef radial_basis_kernel<sample_type> kernel_type;
    kcentroid<kernel_type> kc(kernel_type(0.1), 0.01, 8);
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

    PlotClusters(plot_clusters, "K-Means", "../results/" +  name + "-kmeans.png");
}


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
      long idx1 = std::distance(samples_->begin(),
                               std::find(samples_->begin(), samples_->end(), a));
      long idx2 = std::distance(samples_->begin(),
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


  PlotClusters(plot_clusters, "Spectral clustering", "../results/" +  name + "-spectral.png");
}


int main(int argc, char** argv){

//Let the client choose the model:
std::cout << "Please input the model: Enter 1, 2, 3, 4 or 5: \n ";
std::cout<< "case(1):DoHierarhicalClustering(inputs, num_clusters, dataset)\n";
std::cout << "case(2):DoGraphClustering(inputs, dataset)\n";
std::cout << "case(3):DoKMeansClustering(inputs, num_clusters, dataset)\n";
std::cout << "case(4):DoGraphNewmanClustering(inputs, dataset)\n";
std::cout << " case(5):DoSpectralClustering(inputs, num_clusters, dataset)\n";
int option;
std::cin >> option;
std::cout << "\n\n\n";

  if (argc > 1) {
    auto base_dir = fs::path(argv[1]);
    for (auto& dataset : data_names) {
      auto dataset_name = base_dir / dataset;
      if (fs::exists(dataset_name)){
        std::ifstream file(dataset_name);
        matrix<DataType> data;
        file >> data;

        auto inputs = dlib::subm(data, 0, 1, data.nr(), 2);
        auto labels = dlib::subm(data, 0, 3, data.nr(), 1);

        auto num_samples = inputs.nr();
        auto num_features = inputs.nc();
        std::size_t num_clusters = 
            std::set<double>( labels.begin(), labels.end()).size();
        if (num_clusters < 2)
            num_clusters = 3;

        std::cout << dataset << "\n"
                  << "Num samples: " << num_samples 
                  << " num features: " << num_features
                  << " num clusters: " << num_clusters << std::endl;
                  switch(option)
                  {
                      case(1):
                      DoHierarhicalClustering(inputs, num_clusters, dataset);break;
                      case(2):
                      DoGraphClustering(inputs, dataset);break;
                      case(3):
                      DoKMeansClustering(inputs, num_clusters, dataset);break;
                      case(4):
                      DoGraphNewmanClustering(inputs, dataset);break;
                      case(5):
                      DoSpectralClustering(inputs, num_clusters, dataset);break;
                      default:
                      throw std::invalid_argument("error! please give a correct option here!\n");break;
                  };

        
      }
      else{
        std::cerr << "Dataset file " << dataset_name << "missed\n";
    }
  }
 }
  else {
    std::cerr << "Please provide path to the datasets folder\n";
  }


  return 0;
}



    
