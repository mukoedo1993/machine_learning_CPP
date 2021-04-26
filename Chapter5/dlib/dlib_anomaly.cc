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

   void MultivariateGaussianDist(const Matrix& normal,
                                const Matrix& test,
                                const std::string& file_name) {
   
   // assume that rows are samples and columns are features
   // calculate per feature mean
   dlib::matrix<double> mu(1, normal.nc());
   dlib::set_all_elements(mu, 0);

   /*!
    const matrix_exp colm (
        const matrix_exp& m,
        long col 
    );
        requires
            - 0 <= col < m.nc()
        ensures
            - returns a matrix R such that:
                - R.nr() == m.nr() 
                - R.nc() == 1
                - for all valid i:
                  R(i) == m(i,col)
    !*/
   for (long c = 0; c < normal.nc(); ++c) {
       auto col_mean = dlib::mean(dlib::colm(normal, c));
       dlib::set_colm(mu, c) = col_mean;
   }

   // calculate covariance matrix
   dlib::matrix<double> cov(normal.nc(), normal.nc());
   dlib::set_all_elements(cov, 0);
   for (long r = 0; r < normal.nr(); ++r) {
       auto row = dlib::rowm(normal, r);
       cov += dlib::trans(row - mu ) * (row - mu);
   }
   cov *= 1.0 / normal.nr();
   double cov_det = dlib::det(cov);
   dlib::matrix<double> cov_inv = dlib::inv(cov);


   auto first_part = 
        1. / std::pow(2. * M_PI, normal.nc() / 2.) / std::sqrt(cov_det);

   // define probability function
   auto prob = [&](const dlib::matrix<double>& sample) {
       dlib::matrix<double> s = sample - mu;
       dlib::matrix<double> exp_val_m = s * (cov_inv * dlib::trans(s));
       double exp_val = -0.5 * exp_val_m(0, 0);
       double p = first_part * std::exp(exp_val);
       return p;
   };    


   Clusters clusters;  // there will two clusters with normal and anomaly
   double  prob_threshold = 0.001;

   auto detect = [&](auto samples) {
       for ( long r = 0; r <samples.nr(); ++r) {
           auto row = dlib::rowm(samples, r);
           double x = row(0, 0);
           double y = row(0, 1);
           auto p = prob(row);
           if(p >= prob_threshold) {
               clusters[0].first.push_back(x);
               clusters[0].second.push_back(y);
           } else {
               clusters[1].first.push_back(x);
               clusters[1].second.push_back(y);
           }
       }
   };


   detect(normal);
   detect(test);       
   PlotClusters(clusters, "Multivariate Gaussian Distribution", file_name);                  
                                
}


void OneClassSvm(const Matrix& normal,
                const Matrix& test,
                const std::string& file_name) {
                 // line 118   
                }