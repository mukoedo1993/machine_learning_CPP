#ifndef ISOLATION_FOREST_H
#define ISOLATION_FOREST_H

#include <algorithm>
#include <cassert>
#include <iterator>
#include <memory>
#include <random>
#include <unordered_set>
#include <vector>
/*
Isolation forest algorithms can be easily implemented in pure C++ because its logic is pretty straightforward.
Also, there are no implementations of this algorithm in popular libraries. Let's assume that our implementation will
only be used with two-dimensional data. We are going to detect anomalies in a range of samples where each sample contains
the same number of features.

Because our dataset is large enough, we can define a wrapper for the actual data container. This allows us to reduce the 
number of copy operations we perform on the actual data:
*/
namespace iforest {

    using DataType = double;
    template <size_t Cols>
    using Sample = std::array<DataType, Cols>;
    template <size_t Cols>
    using Dataset = std::vector<Sample<Cols>>;
    
    /*
    The CalcC() function can be implemented in the following way,
    according to the formula from the original paper, which describes the
    isolation forest algorithm:
    */
    double CalcC(size_t n) {
        double c = 0;
        if (n > 1)
         c = 2 * ( log(n - 1) + 0.5772156649) - (2 * (n - 1) / n);
         return c;
    }

    template <size_t Cols>
    struct DatasetRange {
        /*
        The DatasetRange type holds a reference to the vector of Sample type objects and to the container of indices
        that point to the samples in the dataset. These indices define the exact dataset objects that this DatasetRange
        object points to.
        */
        DatasetRange(std::vector<size_t>&& indices_, /*rvalue reference here*/
                    const Dataset<Cols>* dataset_)
                    : indices(std::move(indices_)), dataset(dataset_) {}
   //A move constructor allows the resources owned by an rvalue object to be moved into an lvalue without creating its copy. 
        size_t size() const {return indices.size();}
        DataType at(size_t row, size_t col) const {
            return (*dataset)[indices[row]][col];
        }
        std::vector<size_t> indices;
        const Dataset<Cols>* dataset;
    };

    // Next, we define the elements of the isolation tree, with the first one being the Node type:
    struct Node {
        /*
        This 
        */
        Node() {}
        Node (const Node&) = delete;
        Node& operator=(const Node&) = delete;
        Node(std::unique_ptr<Node> left,
            std::unique_ptr<Node> right,
            size_t split_col,
            DataType split_value)
            : left(std::move(left)),
              right(std::move(right)),
              split_col(split_col),
              split_value(split_value) {}
        Node(size_t size) : size(size), is_external(true) {}


        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        //in-class initializer:
        // When a member is omitted from the constructor initializer list, it is
        // implicitly initialized using the same process as is used by the synthesized default
        //constructor. In this case, those memebers are initialized by the in-class initializers.
        size_t split_col{0};
        DataType split_value{0};
        size_t size{0};
        bool is_external{false};
        // This type is a regular tree node structure. The following memebers are specific to the
        // isolation tree algorithm:
        /*
        split_col : This is the index of the feature column where the algorithm caused a split.
        split_value : This is the value of the feature where the algorithm caused a split.
        size : This is the number of underlying items for the node.
        is_external: This is the flag that indicates whether the node is a leaf.
        */
    };


    /*
    Taking the Node type as a basis, we can define the procedure of building an isolation tree.
    We aggregate this procedure with the auxiliary IsolationTree type. Because the current algorithm
    is based on random splits, the auxilliary data is the random engine forest.
    */
    /*
    We only need to initialize this object once, and then it will be shared all tree nodes objects.
    This approach allows us to make the results of the algorithm reproducible in the case of 
    constant seeding. Furthermore, it makes debugging the randomized algorithm much simpler:
    */
    template <size_t Cols>
    class IsolationTree {
        public:
         using Data = DatasetRange<Cols>;

         IsolationTree(const IsolationTree&) = delete;
         IsolationTree& operator=(const IsolationTree&) = delete;
         IsolationTree(std::mt19937* rand_engine, Data data, size_t hlim)
           : rand_engine(rand_engine) {
               root = MakeIsolationTree(data, 0, hlim);
        }
        IsolationTree(IsolationTree&& tree) {
            rand_engine = std::move(tree.rand_engine);
            root = std::move(tree.root);
        }

        double PathLength(const Sample<Cols>& sample) {
            return PathLength(sample, root.get(), 0);
        }
        private:
        /*
        Another vital method of the IsolationTree type is the PathLength() method.
        We use for anomaly score calculations. It takes the sample as an input parameter
        and return the amortized path length to the corresponding tree leaf from the root node:
        */
        double PathLength(const Sample<Cols>& sample,
                         const Node* node,
                         double height) {
          assert(node != nullptr);
          if (node->is_external) {
              return height + CalcC(node->size);
          } else {
              auto col = node->split_col;
              if (sample[col] < node->split_value) {
                  return PathLength(sample, node->left.get(), height + 1);
              } else {
                  return PathLength(sample, node->right.get(), height + 1);
              }
           }
        }

        /*
        Next, we'll do the most critical work in the MakeIsolationTree() method, which is used
        in the ctor. to initialize the root data member:

        Initially, we checked the termination conditions to stop the splitting process. If we meet them,
        we return a new node marked as an external leaf. Otherwise, we start splitting the passed data range.
        For splitting, we randomly select the feature column and determine the unique values of the selected feature.
         Then, we randomly select a value from an interval between the max and min values among the feature values from 
         all the samples. After we make these random selections, we compare the values of the selected splitting feature to 
         all the samples from the input data range and put their indices into two lists. One lust is for values higher than 
         the splitting values, while another list is for values that are lower than them. Then, we return a new tree node initialized
         with references to the left and right nodes, which are initialized with recursive calls to the MakeIsolationTree() method.
        */
        std::unique_ptr<Node> MakeIsolationTree(const Data& data,
                                                size_t height,
                                                size_t hlim) {
            auto len = data.size();
            if (height >= hlim || len <=1) {
                return std::make_unique<Node>(len);
            }   else {
                std::uniform_int_distribution<size_t> cols_dist(0, Cols - 1);
                auto rand_col = cols_dist(*rand_engine);

                std::unordered_set<DataType> values;
                for (size_t i = 0; i < len; ++i) {
                    auto value = data.at(i, rand_col);
                    values.insert(value);
                }

                auto min_max = std::minmax_element(values.cbegin(), values.cend());
                std::uniform_real_distribution<DataType> value_dist(*min_max.first,
                                                                   *min_max.second );

                auto split_value = value_dist(*rand_engine);

                std::vector<size_t> indices_left;
                std::vector<size_t> indices_right;
                for (size_t i = 0; i < len; ++i) {
                    auto value = data.at(i, rand_col);
                    if(value < split_value) {
                        indices_left.push_back(data.indices[i]);
                    } else {
                        indices_right.push_back(data.indices[i]);
                    }
                }


                return std::make_unique<Node>(
                    MakeIsolationTree(Data{std::move(indices_left), data.dataset},
                                     height + 1, hlim),
                    MakeIsolationTree(Data{std::move(indices_right), data.dataset},
                                        height + 1, hlim),
                    rand_col, split_value);
                }                                     
            }


        private:
          std::mt19937* rand_engine;
          std::unique_ptr<Node> root;
    };





    /*
    Initially, we checked the termination conditions to stop the splitting process. If we meet them,
    we return a new node marked as an external leaf. Otherwise, we start splitting the passed data
    range. For splitting, we randomly select the feature column and determine the unique values of the 
    selected feature. Then, we randomly select a value from an interval between the max and the min values among
    the feature values from all the samples. After we make these random selections, we compare the values of selected
    splitting feature to all the samples from the input data range and put their indices into two lists. One list is 
    for values higher than the splitting values, while another list is for values that are lower than them. Then, we return
    a new tree node initialized with references to the left and right nodes, which are initialized with recursive calls to
    the MakeIsolationTree() method.
    */




   /*
   The final part of the algorithm's implementation is the creation of the forest. The forest is an array
   of trees built from a limited number of samples, randomly chosen from the original dataset. The number of samples
   used to build the tree is a hyperparameter of this algorithm. Furthermore, this implementation uses heuristics as 
   the stopping criteria, in that, it is a maximum tree height hlim value.

   Let's see how it is used in the tree building procedure. The hlim value is calculated only once, and the following code shows this.
   Moreover, it is based on the No. of samples that are used to build a single tree:

   The tree forest is built in the ctor. of the IsolationForest type. We also calculated the value of the average path length
   of the unsuccessful search in a binary search tree for all of the samples in the ctor. We use this forest in the AnomalyScore() method
   for the actual process of anomaly detection. It implements the formula for the anomaly score value for a given sample. It returns
   a value that can be interpreted in the following way: If the returned value is close to 1, then the sample has anomalous features,
   while if the value is less than 0.5, then we can assume that the sample is a normal one.
   */
    template <size_t Cols>
    class IsolationForest {
        public:
         using Data = DatasetRange<Cols>;

         IsolationForest(const IsolationForest&) = delete;
         IsolationForest& operator=(const IsolationForest&) = delete;
         IsolationForest(const Dataset<Cols>& dataset,
                         size_t num_trees,
                         size_t sample_size)
            : rand_engine(2325) {
            std::vector<size_t> indices(dataset.size());
            std::iota(indices.begin(), indices.end(), 0);


            size_t hlim = static_cast<size_t>(ceil(log2(sample_size)));
            for (size_t i = 0; i < num_trees; ++i) {
                std::vector<size_t> sample_indices;
                std::sample(indices.begin(), indices.end(),
                            std::back_insert_iterator(sample_indices), sample_size, 
                            rand_engine);
                trees.emplace_back(&rand_engine,
                                   Data(std::move(sample_indices), &dataset), hlim);
            }

             double n = dataset.size();
             c = CalcC(n);
            }


            /*
            Finally, we called the AnomalyScore() method for each sample from the dataset in order to detect
            anomalies with thresholds and return their values. In the following graph, we can see the result of
            anomaly detection after using the Isolation Forest algorithm. The red points are the anomalies.
            */
            double AnomalyScore(const Sample<Cols>& sample) {
                double avg_path_length = 0;
                for (auto& tree : trees) {
                    avg_path_length += tree.PathLength(sample);
                }
                avg_path_length /= trees.size();

                double anomaly_score = pow(2, -avg_path_length / c);
                return anomaly_score;
            }
        private:
         std::mt19937 rand_engine;
         std::vector<IsolationTree<Cols>> trees;
         double c{0};
    };

}   // namespace iforest

#endif //ISOLATION_FOREST_H