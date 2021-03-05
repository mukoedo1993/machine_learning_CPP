#include <Eigen/Dense>
#include <Eigen/IterativeLinearSolvers>

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
using std::vector;
using std::iota;//sequentials with a initial value, and ++value at each step.
using std::random_device;//std::random_device is a 
//uniformly-distributed integer random number generator 
//that produces non-deterministic random numbers.

using std::mt19937;
// Mersenne Twister pseudo-random generator 
//of 32-bit numbers with a state size of 19937 bits.
using std::uniform_real_distribution;


using std::tie;//
using std::endl;
using std::cout;


std::pair<Eigen::MatrixXf, Eigen::MatrixXf> GenerateData(size_t n){

    vector<float> x_data(n);
    iota(x_data.begin(),x_data.end(),0);
    vector<float>y_data(n);
    iota(y_data.begin(),y_data.end(),0);


    //mutate data
    random_device rd;
    mt19937 re(rd());
    uniform_real_distribution<float> dist(-1.5f, 1.5f);

    for(auto& x: x_data){
        x += dist(re);
    }

    for (auto& y: y_data){
        y += dist(re);
    }

    // Make result
    Eigen::Map<Eigen::MatrixXf> x(x_data.data(), static_cast<Eigen::Index>(n), 1);
    Eigen::Map<Eigen::MatrixXf> y(y_data.data(), static_cast<Eigen::Index>(n), 1);

    return {x, y};
}


int main() {
    size_t n =1000;
    //generate training data
    Eigen::MatrixXf x1, y;

    //std::tie :Creates a tuple of lvalue references to its arguments or instances of std::ignore.
    tie(x1, y) = GenerateData(n);
    Eigen::MatrixXf x0 = Eigen::MatrixXf::Ones(n, 1);

    //setup lines coeficients y = b(4) + k(0.3)*x
    y.array() *= 0.3f;
    y.array() += 4.f;

    Eigen::MatrixXf x(n, 2);
    x << x0, x1;

    //train estimator
    Eigen::LeastSquaresConjugateGradient<Eigen::MatrixXf>gd;
    gd.setMaxIterations(100);
    gd.setTolerance(0.001f);
    gd.compute(x);
    Eigen::VectorXf b = gd.solve(y);
    cout << "Estimated parameters vector :" << b << endl;

    // normal equations
    Eigen::VectorXf b_norm = (x.transpose() * x).ldlt().solve(x.transpose() * y);
    //ldlt Cholesky decomposition
    cout << "Estimated with normal equation parameters vector :" <<b_norm << endl;

    //predict:
    Eigen::MatrixXf new_x(5, 2);
    new_x << 1, 1, 1, 2, 1, 3, 1, 4, 1, 5;
    auto new_y = new_x.array().rowwise() *b.transpose().array();
    cout << "Predicted values: \n" <<new_y << endl;

    cout<<"b_norm is: "<<b_norm << endl;
    auto new_y_norm = new_x.array().rowwise() * b_norm.transpose().array();
    cout << "Predicted(norm) values: \n" <<new_y_norm << endl;


    return 0;



}

