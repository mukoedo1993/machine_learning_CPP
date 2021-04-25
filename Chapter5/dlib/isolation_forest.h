#ifndef ISOLATION_FOREST_H
#define ISOLATION_FOREST_H

#include <algorithm>
#include <cassert>
#include <iterator>
#include <memory>
#include <random>
#include <unordered_set>
#include <vector>

namespace iforest {

    using DataType = double;
    template <size_t Cols>
    using Sample = std::array<DataType, Cols>;
    template <size_t Cols>
    using Dataset = std::vector<Sample<Cols>>;


    double CalcC(size_t n) {
        double c = 0;
        if (n > 1)
         c = 2 * ( log(n - 1) + 0.5772156649) - (2 * (n - 1) / n);
         return c;
    }

    template <size_t Cols>
    struct DatasetRange {
        DatasetRange(std::vector<size_t>&& indices_, /*rvalue reference here*/
                    const Dataset<Cols>* dataset_)
                    : indices(std::move(indices_)), dataset(dataset_) {}
   //A move constructor allows the resources owned by an rvalue object to be moved into an lvalue without creating its copy. 

        std::vector<size_t> indices;
        const Dataset<Cols>* dataset;
    };


    struct Node {
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

    };



    template <size_t Cols>
    class IsolationTree {
        public:
         using Data = DatasetRange<Cols>;

         IsolationTree(const IsolationTree&) = delete;
         IsolationTree& operator=(const IsolationTree&) = delete;
         IsolationTree(std::mit19937* rand_engine, Data data, size_t hlim)
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

    template <size_t Cols>
    class IsolationForest {
        public:
         using Data = DatasetRange<Cols>;

         IsolationForest(const IsolationForest&) = delete;
         /*line 150!!!!!!!!!!!!!!!!!*/
    };

}

#endif //ISOLATION_FOREST_H