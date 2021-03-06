#include<csv_clone/csv.h>
#include<Eigen/Dense>


#include<experimental/filesystem>//Include the header <filesystem> for access to classes and 
//functions that manipulate and retrieve information about paths, files, and directories.
#include<iostream>
#include<string>
#include<fstream>



namespace fs = std::experimental::filesystem;

/*
One is for reading a row from a file, and it uses the read_row()
method of parameters of different types. 
*/
template<std::size_t... Idx, typename T, typename R>
bool read_row_help(std::index_sequence<Idx...>, T& row, R& r){
    return r.read_row(std::get<Idx>(row)...);
}


/*
We do automatic parameter filling by using the std::index_sequence type
with the std::get function:
*/
template<std::size_t... Idx, typename T>
void fill_values(std::index_sequence<Idx...>,
                T& row,
                std::vector<double>& data){
        data.insert(data.end(), {std::get<Idx>(row)...});
                }

int main(int argc, char** argv){


    std::ofstream ob1;
    ob1.open("output.txt",  std::ofstream::binary | std::ofstream::in);
    if(argc > 1){//To make sure that there is a directory to the file
        auto file_path = fs::path(argv[1]);//To make sure that the file's location address is valid
        if(fs::exists(file_path)){
            const uint32_t columns_num = 5;
            io::CSVReader<columns_num> csv_reader(file_path);

            std::vector<std::string> categorical_column;
            std::vector<double> values;
            using RowType = std::tuple<double, double, double, double, std::string>;
            RowType row;


//Now, we can put all the parts together. We define a loop where we continuously read row values
//and move them to our containers. After we read a row, we check the return value of return value of 
//the read_row() method, which tells us if the read was successful or not. A false value means that we
//have reached the end of the file. In the case of a parsing error, we catch an exception from the io::error
//namespace. There are exception tyoes for different parsing fails. In the following example, we handle number
//parsing errors:
            uint32_t rows_num = 0;
            try{
             bool done = false;
             while (!done){
                 done = !read_row_help(
                     std::make_index_sequence<std::tuple_size<RowType>::value>{}, row, 
                     csv_reader);
                 if (!done){
                     categorical_column.push_back(std::get<4>(row));
                     fill_values(std::make_index_sequence<columns_num - 1>{}, row, 
                                 values);
                     ++rows_num;
                 }
             }
               } catch (const io::error::no_digit& err){
                   // ignore bad formatted samples
                   std::cerr<< err.what() << std::endl;
               }
//Also, notice that we moved only four values to our vector of doubles because the last column
//contains string objects that we put to another vector of categorial values.



        auto x_data = Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic,
                                Eigen::Dynamic, Eigen::RowMajor>>(
                        values.data(), rows_num, columns_num - 1);
                   
                   ob1 <<"\noriginal x_data is: " << x_data << std::endl;

                   //Featured-scaling(Normalization):
                   //Standardiztaion - zero mean + 1 std
                   Eigen::Array<double, 1, Eigen::Dynamic> std_dev = 
                   ((x_data.rowwise() - x_data.colwise().mean())
                      .array()
                      .square()
                       .colwise()
                       .sum() /
                    (x_data.rows() - 1))
                    .sqrt();
        
        Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>x_data_std = 
        (x_data.rowwise() - x_data.colwise().mean()).array().rowwise() /
        std_dev;

        ob1 << x_data_std << std::endl;

        // Min_Max normalization
        Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> x_data_min_max = 
        (x_data.rowwise() - x_data.colwise().minCoeff()).array().rowwise() / 
        (x_data.colwise().maxCoeff() - x_data.colwise().minCoeff()).array();

        ob1<< "\n\n\n####min_max_normalization####\n\n\n" << x_data_min_max << std::endl;

        // Average normalization
        Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> x_data_avg = 
        (x_data.rowwise() - x_data.colwise().mean()).array().rowwise() / 
        (x_data.colwise().maxCoeff() - x_data.colwise().minCoeff()).array();

        ob1 << "\n\n\n####Mean_normalization####\n\n\n" << x_data_avg << std::endl;
        } else {
            std::cerr << "File path is incorrect " << file_path << '\n';
        }
    } else {
        std::cerr << "Please provide a path to a dataset file!" << std::endl;
    }

        //close the file if it is still open
        if(ob1.is_open())ob1.close();
}

