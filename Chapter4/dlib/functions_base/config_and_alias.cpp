#include <dlib/clustering.h>
#include <dlib/matrix.h>
#include <plotcpp_clone/plotcpp/plot.h>

#include <experimental/filesystem>
#include <iostream>
#include <unordered_map>


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