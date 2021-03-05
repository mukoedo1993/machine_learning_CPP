#include<iostream>
#include<dlib/matrix.h>
#include<dlib/svm.h>


#include<iostream>
#include<random>
using std::cout;

float func(float x){
    return 4.f + 0.3f *x; //line coefficients
}

using SampleType = dlib::matrix<double, 1, 1>;
using KernelType = dlib::linear_kernel<SampleType>;


int main(){
    using namespace dlib;
    size_t n = 1000;
    std::vector<matrix<double>> x(n);
    std::vector<float> y(n);

    std::random_device rd;
    std::mt19937 re(rd());
    std::uniform_real_distribution<float> dist(-1.5, 1.5);

    //generate data
    for (size_t i = 0; i < n; ++i){
        x[i].set_size(1, 1);
        x[i](0, 0) = i;

        y[i] = func(i) + dist(re);
    }
    //normalize data

    vector_normalizer<matrix<double>> normalizer_x;
    // let the normalizer learn the mean and std of the samples
    normalizer_x.train(x);
    //now normalize each sample
    for(size_t i = 0; i < x.size(); ++i){
        x[i] = normalizer_x(x[i]);
    }

    krr_trainer<KernelType>trainer;//kernel ridge regression algorithm
    trainer.set_kernel(KernelType());
    decision_function<KernelType> df = trainer.train(x, y);

    //Generate new data
    cout << "Original data \n";
    std::vector<matrix<double>> new_x(5);
    for(size_t i =0; i < 5; ++i)
    {
        new_x[i].set_size(1,1);
        new_x[i](0, 0) = i;
        new_x[i] = normalizer_x(new_x[i]);
        cout << func(i) << std::endl;
    }

    cout <<"Predictions \n";

    for(const auto &v: new_x){
        auto prediction = df(v);
        cout<< prediction << std::endl;
    }

}

/*(base) zcw@mukoedo1993:~/machine_learning_CPP/Chapter1/Dlib/build$ ./linreg_dlib
Original data 
4
4.3
4.6
4.9
5.2
Predictions 
3.9589
4.25896
4.55903
4.85909
5.15916
*/
