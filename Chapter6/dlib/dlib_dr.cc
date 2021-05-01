#include <dlib/image_io.h>
#include <dlib/image_processing.h>
#include <dlib/matrix.h>
#include <dlib/matrix/matrix_utilities.h>
#include <dlib/statistics.h>
#include <plotcpp_clone/plotcpp/plot.h>


#include <experimental/filesystem>
#include <iostream>
#include <unordered_map>

using namespace dlib;
namespace fs = std::experimental::filesystem;

const std::vector<std::string> colors {"black", "red", "blue", "green",
                                      "cyan", "yellow", "brown", "magenta"};


using DataType = double;
using Matrix = matrix<DataType>;
using Coords = std::vector<DataType>;
using PointCoords = std::pair<Coords, Coords>;
using Clusters = std::unordered_map<size_t, PointCoords>;


const std::string photo_file_name{"photo.png"};
const std::string data_file_name{"swissroll.dat"};
const std::string labels_file_name{"swissroll_labels.dat"};


void PlotClusters(const Clusters& clusters,
                 const std::string& name,
                 const std::string& file_name) {
     plotcpp::Plot plt(true);
     // plt.SetTerminal("qt");
     plt.SetTerminal("png");
     plt.SetOutput(file_name);
     plt.SetTitle(name);
     plt.SetXLabel("x");
     plt.SetYLabel("y");
     // plt.SetAutoscale();
     plt.GnuplotCommand("set size square");
     plt.GnuplotCommand("set grid");

     auto draw_state = plt.StartDraw2D<Coords::const_iterator>();
     /*line 43*/
                 }