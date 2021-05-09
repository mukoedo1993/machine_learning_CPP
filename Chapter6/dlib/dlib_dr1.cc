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
using Matrix = dlib::matrix<DataType>;
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
                            cluster.second.first.cbegin(), cluster.second.first.cend(),
                            cluster.second.second.cbegin(),
                            std::to_string(cluster.first) + " cls", params.str()));
     }

     plt.EndDraw2D(draw_state);
     plt.Flush();
                 }

    
    void SammonReduction(const std::vector<Matrix>& data,
                         const std::vector<unsigned long>& labels,
                         long target_dim) {
       /*
       In the dlib library, sammon mapping is implemented with the dlib::sammon_projection tyep.
       We need to create an instance of this type and then use it as a functional object. Functional object
       call arguments are the data that we need to transform and the number of dimensions of the new feature space.
       The input data should be in the form of the std::vector of the single samples of the dlib::matrix type. All
       samples should have the same number of dimensions. The result of using this functional object is a new vector
       of samples with a reduced number of dimensions:
       */
       dlib::sammon_projection sp;
       auto new_data = sp(data, target_dim);


        Clusters clusters;
         for (size_t r = 0; r < new_data.size(); ++r) {
                const Matrix& vec = new_data[r];
                double x = vec(0, 0);
                double y = vec(1, 0);
                auto l = labels[r];
                clusters[l].first.push_back(x);
                clusters[l].second.push_back(y);
              }
               PlotClusters(clusters, "Sammon Mapping", "../results/sammon-dlib.png");
          }


     void PCAReduction(const std::vector<Matrix>& data,
                       const std::vector<unsigned long>& labels,
                       double target_dim) {
           dlib::vector_normalizer_pca<Matrix> pca;
           //See vector_normalizer_pca.txt
           pca.train(data, target_dim / data[0].nr());
           std::vector<Matrix> new_data;
           new_data.reserve(data.size());
           //After the algorithm has been trained. we use the object to 
           //transform individual samples. Take a look at the first loop in
           // the code and notice how the pca(data[i]) call performs this
           // transformation.
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

            PlotClusters(clusters, "PCA", "../results/pca-dlib.png");
            }

    void LDAReduction(const Matrix& data,
                     const std::vector<unsigned long>& labels,
                     unsigned long target_dim) {
        //Prelude:
        /*
        The dlib library also has an implementation of the linear discriminant analysis algorithm,
        which can be used for dimensionality reduction. It's a supervised algorithm, so it needs labeled
        data. This algorithm is implemented with the compute_lda_transform() function, which takes four parameters.
        The first one is the input/output parameter -- as input, it is used to pass input training data (in matrix form)
        and as output, it receives the LDA transformation matrix. The second parameter is the output for the mean values.
        The 3rd parameter is the labels for the input data, while the 4th one is the desired number dimension reduction
        with the dlib lib. ...
        */
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
          /*
          To perform an actual LDA transform after the algorithm has been trained, we multiply our samples
          with the LDA matrix. In our case, we also transposed them.
          */
            Matrix row = transform * dlib::trans(dlib::rowm(data, r)) - mean;
            double x = row(0, 0);
            double y = row(1, 0);
            auto l = labels[static_cast<size_t>(r)];
            clusters[l].first.push_back(x);
            clusters[l].second.push_back(y);
        }


        PlotClusters(clusters, "LDA", "../results/lda-dlib.png");
    }



/*
PCA is one of the most popular dimensionality reduction algorithms and it has a couple
of implementations in the dlib lib. There is the dlib::vector_normalizer_pca type, for which
objects can be used to perform PCA on user data. This implementation also normalizes the data.
In some cases, the automatic normalization is useful because we always have to perform PCA on normalized data.
An object of this type should be parameterized with the input data sample type. After we've instantiated an object
of this parameterized with the input data sample type. After we've instantiated an object of this type, we use the 
train() method to fit the model to our data. The train() method takes std::vector as samples and the eps value as parameters.
The eps value controls how many dimensions should be preserved after the PCA has been transformed.
*/



    void PCACompression(const std::string& image_file, long target_dim) {
       /*
       Prelude: 
       We can use dimensionality reduction algorithms for a slightly different task --
       data compression with information loss. This can be easily demonstrated when applying
       the PCA algorithm to images. Let's implement PCA from scratch with the dlib library using
       SVD decomposition. We can't use an existing implementation because it performs normalization
       in a way we can't fully control.
       */


        //http://dlib.net/dlib/array2d/array2d_kernel.h.html
        //see array2d_document.txt
        array2d<dlib::rgb_pixel> img;
        load_image(img, image_file);// destination source

        array2d<unsigned char> img_gray;
        assign_image(img_gray, img);// destination source
        save_png(img_gray, "../results/original.png");

        array2d<DataType> tmp;
        assign_image(tmp, img_gray);// destination source
        Matrix img_mat = dlib::mat(tmp);
        img_mat /= 255.;    // scale


        std::cout << "Original data size " << img_mat.size() << std::endl;


        //take patches 8x8
        std::vector<Matrix> data;
        int patch_size = 8;


        /*
        After we've loaded the RGB image, we convert it into grayscale and transform its values into floating
        points. The next step is to transform the image matrix into samples that we can use for PCA training.
        THis can be done by splitting the image into rectangular patches that are 8x8 in size with the
        dlib::subm() function and then flattening them with the dlib::reshape_to_column_vector() function:
        */
        for (long r = 0; r < img_mat.nr(); r += patch_size) {
          for (long c = 0; c < img_mat.nc(); c += patch_size) {
            Matrix sm = dlib::subm(img_mat, r, c, patch_size, patch_size);
            data.emplace_back(dlib::reshape_to_column_vector(sm));
          }
        }

        // normalize data
        auto data_mat = mat(data);// see matrix_utilities.h
        Matrix m = mean(data_mat);// see matrix_utilities.h
        Matrix sd = reciprocal(sqrt(variance(data_mat)));
        
        matrix<decltype(data_mat)::type, 0, 1, decltype(data_mat)::mem_manager_type>
          x(data_mat);
          std::vector<double> x_;
        for ( long r = 0; r < x.size(); ++r){
          x(r) = pointwise_multiply(x(r) - m, sd);
        }


        /*
        After we've prepared the data samples, we calculate the covariance matrix with the
        dlib::covariance() function and perform SVD with the dlib::svd() function. The SVD 
        results are the eigenvalues matrix and the eigenvectors matrix. We sorted the eigenvectors
        according to the eigenvalues and left only a small number (in our case, 10 of them) of eigenvectors
        correspondent to the biggest eigenvalues.
        */
        // perform PCA
        Matrix temp, eigen, pca;
        // Compute the svd of the covariance matrix
     
        dlib::svd(covariance(x), temp, eigen, pca);   
        /*
          void svd (
        const matrix_exp& m,
        matrix<matrix_exp::type>& u,
        matrix<matrix_exp::type>& w,
        matrix<matrix_exp::type>& v
    );
        ensures
            - computes the singular value decomposition of m
            - m == #u*#w*trans(#v)
            - trans(#u)*#u == identity matrix
            - trans(#v)*#v == identity matrix
            - diag(#w) == the singular values of the matrix m in no 
              particular order.  All non-diagonal elements of #w are
              set to 0.
            - #u.nr() == m.nr()
            - #u.nc() == m.nc()
            - #w.nr() == m.nc()
            - #w.nc() == m.nc()
            - #v.nr() == m.nc()
            - #v.nc() == m.nc()
            - if DLIB_USE_LAPACK is #defined then the xGESVD routine
              from LAPACK is used to compute the SVD.
        */

  
    /*!
      const matrix covariance (
        const matrix_exp& m
    );
        requires
            - matrix_exp::type == a dlib::matrix object
            - is_col_vector(m) == true
            - m.size() > 1
            - for all valid i, j:
                - is_col_vector(m(i)) == true 
                - m(i).size() > 0
                - m(i).size() == m(j).size() 
                - i.e. m contains only column vectors and all the column vectors
                  have the same non-zero length
        ensures
            - returns the unbiased sample covariance matrix for the set of samples
              in m.  
              (i.e. 1.0/(m.nr()-1)*(sum of all (m(i) - mean(m))*trans(m(i) - mean(m))))
            - the returned matrix will contain elements of type matrix_exp::type::type.
            - the returned matrix will have m(0).nr() rows and columns.
    !*/

// ----------------------------------------------------------------------------------------
        Matrix eigenvalues = diag(eigen);
        rsort_columns(pca, eigenvalues);      
    /*!
     template <typename T>
    void rsort_columns (
        matrix<T>& m,
        matrix<T>& v
    );
        requires
            - is_col_vector(v) == true
            - v.size() == m.nc()
            - m and v both contain the same type of element
        ensures
            - the dimensions for m and v are not changed
            - sorts the columns of m according to the values in v.
              i.e. 
                - #v == the contents of v but in sorted order according to
                  operator>.  So larger elements come first.
                - Let #v(new(i)) == v(i) (i.e. new(i) is the index element i moved to)
                - colm(#m,new(i)) == colm(m,i) 
    !*/

// ----------------------------------------------------------------------------------------


        // leave only required number of principal components
        pca = trans(colm(pca, range(0, target_dim)));


        // dimensionality reduction
        /*
        Our PCA transformation matrix is called pca. We used it to reduce the
        dimensions of each of our samples with simple matrix multiplication. 
        Look at the following cycle and notice the pca * data[i] operation:
        */
        std::vector<Matrix> new_data;
        new_data.reserve(data.size());
        size_t new_size = 0;
        for (size_t i = 0; i < data.size(); ++i) {
          new_data.emplace_back(pca * data[i]);
          new_size += static_cast<size_t>(new_data.back().size());
        }


        std::cout << "New data size " <<new_size + static_cast<size_t>(pca.size())
                  << std::endl;

        // unpack data
        /*
        Our data has been compressed and we can see its new size in the console output. Now,
        we can restore the original dimension of the data to be able to see the image. To do this,
        we need to use the transposed PCA matrix to multiply the reduced samples. Also, we need to
        denormalize the restored sample to get actual pixel values. This can be done by multiplying the
        std deviation and adding the mean we got from the previous steps: 
        */
        auto pca_matrix_t = dlib::trans(pca);
        Matrix isd = dlib::reciprocal(sd);
        for (size_t i = 0; i < new_data.size(); ++i) {
          Matrix sample = pca_matrix_t * new_data[i];
          new_data[i] = dlib::pointwise_multiply(sample, isd) + m;
        }

        // After we've restored the pixel values, we reshape them and place them in their original
        // location in the image:
        size_t i = 0;
        for ( long r = 0; r < img_mat.nr(); r += patch_size) {
          for (long c = 0; c < img_mat.nc(); c += patch_size) {
            auto sm = dlib::reshape(new_data[i], patch_size, patch_size);
                /*!
                  const matrix_exp reshape (
        const matrix_exp& m,
        long rows,
        long cols
    );
        requires
            - m.size() == rows*cols
            - rows > 0
            - cols > 0
        ensures
            - returns a matrix M such that: 
                - M.nr() == rows
                - M.nc() == cols
                - M.size() == m.size()
                - for all valid r and c:
                    - let IDX = r*cols + c
                    - M(r,c) == m(IDX/m.nc(), IDX%m.nc())

            - i.e. The matrix m is reshaped into a new matrix of rows by cols
              dimension.  Additionally, the elements of m are laid into M in row major 
              order.
    !*/




            dlib::set_subm(img_mat, r, c, patch_size, patch_size) = sm;
            ++i;
          }
        }

        img_mat *= 255.0;
        assign_image(img_gray, img_mat);
        equalize_histogram(img_gray);
        save_png(img_gray, "../results/compressed.png");

       
    }

  
    int main(int argc, char** argv) {
      if (argc > 1) {
        try {
          auto data_dir = fs::path(argv[1]);
          auto data_file_path = data_dir / data_file_name;
          auto labels_file_path = data_dir / labels_file_name;
          auto photo_file_path = data_dir / photo_file_name;
          if (fs::exists(data_file_path) && fs::exists(labels_file_path) &&
              fs::exists(photo_file_path)) {
                matrix<DataType> data;
                std::vector<Matrix> vdata;
                {
                  std::ifstream file(data_file_path);
                  file >> data;
                  vdata.reserve(static_cast<size_t>(data.nr()));
                  for (long row = 0; row < data.nr(); ++row) {
                    vdata.emplace_back(dlib::reshape_to_column_vector(
                         dlib::subm_clipped(data, row, 0, 1, data.nc())));
                  }
                }
                matrix<DataType> labels;
                std::vector<unsigned long> vlabels;
                {
                  std::ifstream file(labels_file_path);
                  file >> labels;
                  vlabels.resize(static_cast<size_t>(labels.nr()));
                  for (long r = 0; r < labels.nr(); ++r) {
                    vlabels[static_cast<size_t>(r)] =
                    static_cast<unsigned long>(labels(r, 0));
                  }
                }

                PCACompression(photo_file_path, 10);
                 int target_dim = 2;
                 LDAReduction(data, vlabels, target_dim);
                 PCAReduction(vdata, vlabels, target_dim);
                 SammonReduction(vdata, vlabels, target_dim);
              }

        } catch (const std::exception& err) {
          std::cerr << err.what();
        }
      }  else {
          std::cerr << "Please provide path to the dataset folder\n";
        }

        return 0;
    }