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
     for (auto& cluster : clusters) {
         std::stringstream params;
         params << "lc rgb'" <<colors[cluster.first] << "' pt 7";
         plt.AddDrawing(draw_state,
                        plotcpp::Points(
                            cluster.second.first.cbegin(), cluster.second.first.cend()
                            cluster.second.second.begin(),
                            std::to_string(cluster.first) + " cls", params.str()));
     }

     plt.EndDraw2D(draw_state);
     plt.Flush();
                 }

    
    void SammonReduction(const std::vector<Matrix>& data,
                         const std::vector<unsigned long>& labels,
                         long target_dim) {
                             dlib::sammon_projection sp;
                             auto new_data = sp(data, target_dim);


                             Clusters clusters;
                             for (size_t r = 0; r < new_data.size(); ++r) {
                                 Matrix vec = new_data[r];
                                 double x = vec(0, 0);
                                 double y = vec(1, 0);
                                 auto l = labels[r];
                                 clusters[l].first.push_back(x);
                                 clusters[l].second.push_back(y);
                             }



                             PlotClusters(clusters, "Sammon Mapping", "sammon-dlib.png");
                         }


                         void PCAReduction(const std::vector<Matrix>& data,
                                           const std::vector<unsigned long>& labels,
                                           double target_dim) {
                              dlib::vector_normalizer_pca<Matrix> pca;
                              pca.train(data, target_dim / data[0].nr());
                              std::vector<Matrix> new_data;
                              new_data.reserve(data.size());
                              for (size_t i = 0; i < data.size(); ++i) {
                                  new_data.emplace_back(pca(data[i]));
                              }

                              Clusters clusters;
                              for (size_t r = 0; r < new_data.size(); ++r) {
                                  const Matrix& vec = new_data[r];
                                  double x = vec(0 , 0);
                                  double y = vec(1 , 0);
                                  auto l = labels[r];
                                  clusters[l].first.push_back(x);
                                  clusters[l].second.push_back(y);
                              }

                              PlotClusters(clusters, "PCA", "pca-dlib.png");
            }

    void LDAReduction(const Matrix& data,
                     const std::vector<unsigned long>& labels,
                     unsigned long target_dim) {
         dlib::matrix<DataType, 0, 1> mean;
         Matrix transform = data;
         dlib::compute_lda_transform(transform, mean, labels, target_dim);
         /*
          void compute_lda_transform (
        matrix<T>& X,
        matrix<T,0,1>& M,
        const std::vector<unsigned long>& row_labels,
        unsigned long lda_dims = 500,
        unsigned long extra_pca_dims = 200
    );
        requires
            - X.size() != 0
            - row_labels.size() == X.nr()
            - The number of distinct values in row_labels > 1
            - lda_dims != 0
        ensures
            - We interpret X as a collection X.nr() of input vectors, where each row of X
              is one of the vectors.
            - We interpret row_labels[i] as the label of the vector rowm(X,i).
            - This function performs the dimensionality reducing version of linear
              discriminant analysis.  That is, you give it a set of labeled vectors and it
              returns a linear transform that maps the input vectors into a new space that
              is good for distinguishing between the different classes.  In particular,
              this function finds matrices Z and M such that:
                - Given an input vector x, Z*x-M, is the transformed version of x.  That is,
                  Z*x-M maps x into a space where x vectors that share the same class label
                  are near each other. 
                - Z*x-M results in the transformed vectors having zero expected mean.
                - Z.nr() <= lda_dims
                  (it might be less than lda_dims if there are not enough distinct class
                  labels to support lda_dims dimensions).
                - Z.nc() == X.nc()
                - We overwrite the input matrix X and store Z in it.  Therefore, the
                  outputs of this function are in X and M.
            - In order to deal with very high dimensional inputs, we perform PCA internally
              to map the input vectors into a space of at most lda_dims+extra_pca_dims
              prior to performing LDA. 
         */

        Clusters clusters;
        for (long r = 0; r < data.nr(); ++r) {
            Matrix row = transform * dlib::trans(dlib::rowm(data, r)) - mean;
            double x = row(0, 0);
            double y = row(1, 0);
            auto l = labels[static_cast<size_t>(r)];
            clusters[l].first.push_back(x);
            clusters[l].second.push_back(y);
        }


        PlotClusters(clusters, "LDA", "lda-dlib.png");
    }


    void PCACompression(const std::string& image_file, long target_dim) {
        /*LINE 120! OF*/
        //https://github.com/PacktPublishing/Hands-On-Machine-Learning-with-CPP/blob/master/Chapter06/dlib/dlib-dr.cc
    }
