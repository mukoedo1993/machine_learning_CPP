
#include <dlib/clustering.h>
#include <dlib/matrix.h>
#include <plotcpp_clone/plotcpp/plot.h>


#include <experimental/filesystem>
#include <iostream>
#include <unordered_map>

# ifndef PLOT_CLUSTER_H
# define PLOT_CLUSTER_H
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



#endif