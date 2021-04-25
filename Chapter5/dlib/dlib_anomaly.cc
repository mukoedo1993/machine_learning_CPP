#include <dlib/matrix.h>
#include <dlib/svm.h>
#include <plotcpp_clone/plotcpp/plot.h>

#include "isolation_forest.h"


#include <experimental/filesystem>
#include <iostream>
#include <unordered_map>


using namespace dlib;
namespace fs = std::experimental::filesystem;

const std::vector<std::string> colors{"black", "red", "blue", "green", 
                                      "cyan", "yellow", "brown", "magenta"};

using DataType = double;
using Matrix = matrix<DataType>;
using Coords = std::vector<DataType>;
using PointCoords = std::pair<Coords, Coords>;
using Clusters = std::unordered_map<size_t, PointCoords>;

void PlotClusters(const Clusters& clusters,
                  const std::string& name,
                  const std::string& file_name) {
    plotcpp::Plot plt(true);
    plt.SetTerminal("png");
    plt.SetOutput(file_name);
    plt.SetTitle(name);
    plt.SetXLabel("x");
    plt.SetYLabel("y");
    // plt.SetAutoscale();
    plt.GnuplotCommand("set size square");
    plt.GnuplotCommand("set grid");

    auto draw_state = plt.StartDraw2D<Coords::const_iterator>();
    for (auto& cluster : clusters) {
        std::stringstream params;
        params << "lc rgb '" << colors[cluster.first] << "' pt 7";
        plt.AddDrawing(draw_state,
                       plotcpp::Points(
                           cluster.second.first.begin(), cluster.second.first.end(),
                           cluster.second.second.begin(),
                           std::to_string(cluster.first) + " cls", params.str()));
        }
        
        plt.EndDraw2D(draw_state);
        plt.Flush();
    }

    /*line 52*/