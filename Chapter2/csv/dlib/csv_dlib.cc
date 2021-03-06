#include <dlib/dnn.h>
#include<dlib/matrix.h>

#include <experimental/filesystem>
#include <iostream>
#include <random>
#include <regex>
#include <sstream>

namespace fs = std::experimental::filesystem;

int main(int argc, char** argv){
    using namespace dlib;
    if(argc > 1){
        if(fs::exists(argv[1])){
            std::stringstream str_stream;
        {
        //replace categorial values with numeric ones
        std::ifstream data_stream(argv[1]);
        std::string data_string((std::istreambuf_iterator<char>(data_stream)),
                                std::istreambuf_iterator<char>());
        //std::istreambuf_iterator is a single-pass input iterator that reads successive 
        //characters from the std::basic_streambuf object for which it was constructed.

        //replace string labels, because parssr can't handle strings
        data_string = 
            std::regex_replace(data_string, std::regex("Iris-setosa"), "1");

        data_string = 
            std::regex_replace(data_string, std::regex("Iris_versicolor"), "2");

        data_string = 
            std::regex_replace(data_string, std::regex("Iris-virginica"), "3");


            str_stream << data_string;
       }

       matrix<double> data;
       str_stream >> data;


       std::cout << data << std::endl;

       matrix<double> x_data = subm(data, 0, 0, data.nr(), data.nc() -1);

       std::vector<matrix<double>> samples;
       for (int r = 0; r < x_data.nr(); ++r){
           samples.push_back(rowm(x_data, r));
       }

       // Normalization
       // Standardization
       matrix<double> m(mean(mat(samples)));//mu
       matrix<double> sd(reciprocal(stddev(mat(samples))));//sigma**-1 pointwise reciprocal...

       for (size_t i = 0; i < samples.size(); ++i)                                            
       {samples[i] = pointwise_multiply(samples[i] - m, sd);}

     std::cout << mat(samples) << std::endl;

     //Another approach
     // vector_normalizer <matrix<double>> normalizer;
     // samples normalizer train(samples)
     // samples = normalizer(samples);
    } else {
        std::cerr << "Invalid file path "<< argv[1] << std::endl;
    }
    }else{
        std::cerr << "Please provide a path to a dataset\n";
    }
}
/*
(base) zcw@mukoedo1993:~/machine_learning_CPP/Chapter2/csv/dlib/build$ ./linalg_dlib data.csv
 10  12 1.3 
2.4 2.6 4.8 
5.9 8.7 6.3 

 1.02525 0.887678 
                     
-0.972674  -1.08339 
                     
-0.052577  0.195709 
                     
*/