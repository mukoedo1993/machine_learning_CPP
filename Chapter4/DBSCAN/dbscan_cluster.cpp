#include <dlib/clustering.h>
#include <dlib/matrix.h>
#include <plotcpp_clone/plotcpp/plot.h>

#include <experimental/filesystem>
#include <iostream>
#include <unordered_map>
#include <utility>
//This object is intended to represent an edge in an undirected graph which has data samples at its vertices.
// Therefore, it is the undirected version of ordered_sample_pair.

#define UNVISITED -1
#define NOISE -2

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




typedef matrix<double, 2, 1> sample_type;
using Neighbors = std::unordered_map<sample_type, int>;

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

//Here, we use Euclidean distance
DataType disFunc(const sample_type& lhs, const sample_type &rhs)
{
   return sqrt(pow(lhs(1,0)-rhs(1, 0),2.) + pow(lhs(2 ,0) - rhs(2, 0),2.));
}



Neighbors RangeQuery_DBSCAN(const std::unordered_map<sample_type, int>& DB,
                             const std::function<DataType(sample_type, sample_type)> distFunc,
                             const std::pair<sample_type, int>& Q,
                             DataType epsilon
                             )
{
  
  Neighbors N= {Q};
  for (auto P = DB.begin(); P != DB.end(); P++){
      if(disFunc(P->first, Q.first) <= epsilon)
      N.insert(*P);
  }

  return N;
}


template <typename I>
void DoDBSCANClustering(const I& inputs,
                        double epsilon,
                        size_t minPts,
                        const std::string& name){

std::unordered_map<sample_type,int> samples;
for ( long i = 0; i != inputs.nr(); ++i){samples.insert({dlib::trans(dlib::subm(inputs, i, 0, 1, 2)), UNVISITED});}


int C = 0;
/*To be continued...*/
for(auto it = samples.begin(); it != samples.end(); ++it ){
  if(it->second != unvisited)continue;
  Neighbors N = RangeQueryDBSCAN(samples, disFunc, it->first, epsilon);
  N.reserve(samples.size());
  if(N.size() < minPts){
   it->second = NOISE;
   continue;
  }

  C = C + 1;
  it->second = C;
  Neighbors S = N; S.erase(it->first);
  S.reserve(samples.size());
  for ( auto it1 = S.begin(); it1 != S.end(); it++){
     if(samples(it1->first) == NOISE )
      samples(it1->first) = C;
    if(samples(it1->first)!=UNVISITED)continue;

    samples(it1->first) = C;
    Neighbors N = RangeQueryDBSCAN(samples, disFunc, it1->first, epsilon); 
    if(N.size() >= minPts )
     S.insert(N.begin(),N.end());
  }
   Clusters ready_to_plot;
   for(auto it2 = samples.begin(); it2 != samples.end(); it2++ ){
     if(it2->second == NOISE)
     continue;
     ready_to_plot.insert({it2->second,std::make_pair<double, double>((it2->first)(0, 0),(it2->second)(1, 0));});
   }
  PlotClusters(ready_to_plot, "DBSCAN clustering", "../results/" +  name + "-DBSCAN.png");
}

                        }


int main(int argc, char** argv){

//Let the client choose the model:
//Here, DBSCAN.



int option;
std::cin >> option;
std::cout << "\n\n\n";

  if (argc > 3) {
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
        if (num_clusters < 2){
            num_clusters = 3;

        std::cout << dataset << "\n"
                  << "Num samples: " << num_samples 
                  << " num features: " << num_features
                  << " num clusters: " << num_clusters << std::endl;
          double epsilon = atof(argv[2]);
          size_t minPtrs = atoi(argv[3]);
            DoDBSCANClustering(inputs, epsilon, minPtrs, dataset_name);    
        
         }
        else{std::cerr << "dataset file " << dataset_name << "missed. Please enter in the form ./dbscan_cluster <datafile> <epsilon> <minPtrs>\n";}
       }
     }
  }
  else {
    std::cerr << "Please provide path to the datasets folder\n";
  }


  return 0;
}

