
#include <plotcpp_clone/plotcpp/plot.h>

#include <shogun/base/init.h>
#include <shogun/base/some.h>
#include <shogun/converter/FactorAnalysis.h>
#include <shogun/converter/Isomap.h>
#include <shogun/converter/MultidimensionalScaling.h>
#include <shogun/converter/TDistributedStochasticNeighborEmbedding.h>
#include <shogun/converter/ica/FastICA.h>
#include <shogun/io/File.h>
#include <shogun/kernel/GaussianKernel.h>
#include <shogun/lib/SGMatrix.h>
#include <shogun/lib/SGStringList.h>
#include <shogun/lib/SGVector.h>
#include <shogun/preprocessor/KernelPCA.h>
#include <shogun/preprocessor/PCA.h>
#include <shogun/util/factory.h>

#include <experimental/filesystem>
#include <iostream>
#include <unordered_map>
#include <cstdlib>

namespace fs = std::experimental::filesystem;

using namespace shogun;
using DataType = float64_t;
using Matrix = SGMatrix<DataType>;

const std::vector<std::string> colors{"black", "red", "blue", "green", "cyan"};

using Coords = std::vector<DataType>;
using PointCoords = std::pair<Coords, Coords>;
using PointCoords3d = std::tuple<Coords, Coords, Coords>;
using Clusters = std::unordered_map<index_t, PointCoords>;

int main()
{
    Some<CDenseFeatures<DataType>> features;
}