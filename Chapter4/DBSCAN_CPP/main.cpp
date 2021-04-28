#include <stdio.h>
#include <iostream>
#include "dbscan.h"

#include <dlib/clustering.h>
#include <dlib/matrix.h>
#include <plotcpp_clone/plotcpp/plot.h>
#include <experimental/filesystem>
#include <utility>
#include <unordered_map>
namespace fs = std::experimental::filesystem;
//#define MINIMUM_POINTS 4     // minimum number of cluster
//#define EPSILON (0.75*0.75)  // distance for clustering, metre^2

const std::vector<std::string> data_names{
    "dataset0.csv"
    //, "dataset1.csv",
    //"dataset2.csv", "dataset3.csv",
    //"dataset4.csv", "dataset5.csv"
};

const std::vector<std::string> colors{"black", "red", "blue", "green",
                "cyan", "yellow", "brown", "magenta"};

using DataType = double;
using Coords = std::vector<DataType>;
using PointCoords = std::pair<Coords, Coords>;
using Clusters = std::unordered_map<int, PointCoords>;




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
    std::cout <<"\n\n\n" <<__LINE__ << std::endl;
    auto draw_state = plt.StartDraw2D<Coords::const_iterator>();
    std::cout <<"\n\n\n" <<__LINE__ << std::endl;
    for (auto& cluster : clusters) {
         std::cout <<"\n\n\n" <<__LINE__ << std::endl;
        std::stringstream params;
        if(cluster.first == -1) continue;
         std::cout <<"\n\n\n" <<__LINE__ << std::endl;
        std::cout << "lc rgb '" << colors.at(cluster.first) << "'pt 7";
        params << "lc rgb '" << colors.at(cluster.first) << "'pt 7";
       std::cout << __LINE__ << std::endl;
        plt.AddDrawing(draw_state,
                        plotcpp::Points(
                        cluster.second.first.begin(), cluster.second.first.end(),
                        cluster.second.second.begin(),
                        std::to_string(static_cast<size_t>(cluster.first)) + " cls", params.str()));    
                        
    }
    
    plt.EndDraw2D(draw_state);
    plt.Flush();
}
/*
void readBenchmarkData(vector<Point>& points)
{
    // load point cloud. (We use dlib lib here)

    FILE *stream;
    stream = fopen ("benchmark_hepta.dat","ra");

    unsigned int minpts, num_points, cluster, i = 0;
    double epsilon;
    fscanf(stream, "%u\n", &num_points);

    Point *p = (Point *)calloc(num_points, sizeof(Point));

    while (i < num_points)
    {
          fscanf(stream, "%f,%f,%f,%d\n", &(p[i].x), &(p[i].y), &(p[i].z), &cluster);
          p[i].clusterID = UNCLASSIFIED;
          points.push_back(p[i]);
          ++i;
    }

    free(p);
    fclose(stream);
}
*/
void printResults(vector<Point>& points, int num_points)
{
    int i = 0;
    printf("Number of points: %u\n"
        " x     y     z     cluster_id\n"
        "-----------------------------\n"
        , num_points);
    while (i < num_points)
    {
          printf("%5.2lf %5.2lf %d\n",
                 points[i].x,
                 points[i].y,
                 points[i].clusterID);
          ++i;
    }
}

int main(int argc, char** argv)
{    
    if(argc > 3){
    auto base_dir = fs::path(argv[1]);
    double epsilon = atof(argv[2]);
    double minimum_points = atoi(argv[3]);
    for(auto & dataset : data_names ) {
        auto dataset_name = base_dir / dataset;

        if (fs::exists(dataset_name)){
        std::ifstream file(dataset_name);
        dlib::matrix<DataType> data;
        file >> data;

        //auto inputs = dlib::subm(data, 0, 1, data.nr(), 2);
        //auto labels = dlib::subm(data, 0, 3, data.nr(), 1);
        vector<Point> points;
        for ( int i = 0; i < data.nr(); i++){
            points.emplace_back(data(i, 1), data(i, 2), UNCLASSIFIED);
            //points.back().clusterID = UNCLASSIFIED;
        }

        Clusters clusters;

        DBSCAN ds(minimum_points, epsilon, points);
 
        ds.run();

        for (const auto& point : ds.m_points){
            clusters[point.clusterID].first.push_back(point.x);
            clusters[point.clusterID].second.push_back(point.y);
            std::cout << point.clusterID << point.x << point.y << std::endl;
        }

    
        

        std::cout << " file name is: "<< dataset_name << "\n\n\n";
        //printResults(ds.m_points, ds.getTotalPointSize());  
        std::cout << "\n\n\n";
        std::cout <<__LINE__ << std::endl << std::endl;
        PlotClusters(clusters, "DBSCAN clustering", "../results/" +  dataset + "-dbscans.png");


      }
      else{
        std::cerr << "Dataset file " << dataset_name << "missed. Please provide in the correct form.\n";
    }
    }
    

    // read point data
    dlib::matrix<double> mat;




    // constructor
   

    // main loop
    

    // result of DBSCAN algorithm
      
    }
    else {
        std::cerr <<" Please provide the data's folder!!!\n\n";
    }
    return 0;
}
