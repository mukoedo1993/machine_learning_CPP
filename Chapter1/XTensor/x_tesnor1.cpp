#include <xtensor-blas/xlinalg.hpp>
#include <xtensor/xadapt.hpp>
#include <xtensor/xarray.hpp>
#include <xtensor/xbuilder.hpp>
#include <xtensor/xeval.hpp>
#include <xtensor/xio.hpp>
#include <xtensor/xrandom.hpp>

#include <iostream>
#include <vector>

int main() {
  {
    // declaration of dynamically sized array
    {
      std::vector<uint64_t> shape = {3, 2, 4};
      xt::xarray<double, xt::layout_type::row_major> a(shape);
    }
    // declaration of dynamically sized tensor with fixed dimmentions number
    {
      std::array<size_t, 3> shape = {3, 2, 4};
      xt::xtensor<double, 3> a(shape);
    }

    // declaration of tensor with shape fixed at compile time.
    { xt::xtensor_fixed<double, xt::xshape<3, 2, 4>> a; }

    // Initialization of xtensor arrays can be done with C++ initializer lists:
    {
      xt::xarray<double> arr1{{1.0, 2.0, 3.0},
                              {2.0, 5.0, 7.0},
                              {2.0, 5.0, 7.0}};  // initialize a 3x3 array
      std::cout << "Tensor from initializer list :\n" << arr1 << std::endl;
    }
    // Special types of initializers
    {
      std::vector<uint64_t> shape = {2, 2};
      std::cout << "Ones matrix :\n" << xt::ones<float>(shape) << std::endl;
      std::cout << "Zero matrix :\n" << xt::zeros<float>(shape) << std::endl;
      std::cout << "Matrix with ones on the diagonal:\n"
                << xt::eye<float>(shape) << std::endl;
    }
    // Mapping c++ array to tensors
    {
      std::vector<float> data{1, 2, 3, 4};
      std::vector<size_t> shape{2, 2};
      auto data_x = xt::adapt(data, shape);
      std::cout << "Matrix from vector :\n" << data_x << std::endl;
    }
    // Element access
    {
      std::vector<size_t> shape = {3, 2, 4};
      xt::xarray<float> a = xt::ones<float>(shape);
      a(2, 1, 3) = 3.14f;
      std::cout << "Updated element :\n" << a << std::endl;
    }
    // Arithmetic operations examples
    {
      xt::xarray<double> a = xt::random::rand<double>({2, 2});
      xt::xarray<double> b = xt::random::rand<double>({2, 2});

      std::cout << "A: \n" << a << std::endl;
      std::cout << "B: \n" << b << std::endl;

      xt::xarray<double> c = a + b;
      std::cout << "c = a + b \n" << c << std::endl;
      a -= b;
      std::cout << "a -= b \n" << a << std::endl;
      c = xt::linalg::dot(a, b);
      std::cout << "a dot b \n" << c << std::endl;
      c = a + 5;
      std::cout << "c = a + 5 \n" << c << std::endl;
      c = a * b;
      std::cout << "c = a * b \n" << c << std::endl;
    }
    // Partial access to xtensor containers
    {
      xt::xarray<int> a{
          {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
      auto b = xt::view(a, xt::range(1, 3), xt::range(1, 3));
      std::cout << "Partial view on a \n" << b << std::endl;
    }
    // Broadcasting
    {
      auto a = xt::xarray<double>({{1, 2}, {3, 4}});
      auto b = xt::xarray<double>({10, 20});
      b.reshape({2, 1});
      std::cout << "A: \n" << a << std::endl;
      std::cout << "B: \n" << b << std::endl;
      auto c = a + b;
      std::cout << "Columns broadcasting: \n" << c << std::endl;
    }
  }
  return 0;
};
//Run on ther terminal directly: 
/*
(base) zcw@mukoedo1993:~/machine_learning_CPP/real_shogun_test$ g++ x_tesnor1.cpp -I/home/zcw/anaconda3/include -lcblas
(base) zcw@mukoedo1993:~/machine_learning_CPP/real_shogun_test$ ./a.out
Tensor from initializer list :
{{ 1.,  2.,  3.},
 { 2.,  5.,  7.},
 { 2.,  5.,  7.}}
Ones matrix :
{{ 1.,  1.},
 { 1.,  1.}}
Zero matrix :
{{ 0.,  0.},
 { 0.,  0.}}
Matrix with ones on the diagonal:
{{ 1.,  0.},
 { 0.,  1.}}
Matrix from vector :
{{ 1.,  2.},
 { 3.,  4.}}
Updated element :
{{{ 1.      ,  1.      ,  1.      ,  1.      },
  { 1.      ,  1.      ,  1.      ,  1.      }},
 {{ 1.      ,  1.      ,  1.      ,  1.      },
  { 1.      ,  1.      ,  1.      ,  1.      }},
 {{ 1.      ,  1.      ,  1.      ,  1.      },
  { 1.      ,  1.      ,  1.      ,  3.14    }}}
A: 
{{ 0.135477,  0.835009},
 { 0.968868,  0.221034}}
B: 
{{ 0.308167,  0.547221},
 { 0.188382,  0.992881}}
c = a + b 
{{ 0.443644,  1.382229},
 { 1.15725 ,  1.213915}}
a -= b 
{{-0.17269 ,  0.287788},
 { 0.780486, -0.771847}}
a dot b 
{{ 0.000997,  0.19124 },
 { 0.095118, -0.339255}}
c = a + 5 
{{ 4.82731 ,  5.287788},
 { 5.780486,  4.228153}}
c = a * b 
{{-0.053217,  0.157484},
 { 0.147029, -0.766353}}
Partial view on a 
{{ 6,  7},
 {10, 11}}
A: 
{{ 1.,  2.},
 { 3.,  4.}}
B: 
{{ 10.},
 { 20.}}
Columns broadcasting: 
{{ 11.,  12.},
 { 23.,  24.}}

*/