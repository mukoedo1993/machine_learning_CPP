/*
HDF5 is a highly efficient file format for storing datasets and scientific values. The
HighFive library provides a higher-level C++ interface for the C library provided by the HDF
group. In this example, we propose to look at its interface by transforming the dataset used in
the previous section to HDF5 format.
The main concepts of HDF5 format are groups and datasets. Each group can contain other groups
and have attributes of different types. Also, each group can contain a set of dataset entries.
Each dataset is a multidimensional array of values of the same type, which also can have attributes
of different types.
*/


#include"../../json/cpp/reviewsreader.h"


#include <highfive/H5DataSet.hpp>
#include <highfive/H5DataSpace.hpp>
#include <highfive/H5File.hpp>
#include <forward_list>
#include<fstream>

const std::string file_name("../resources/reviews.h5");

//convert dataset from json to hdf5 format and read from it.

int main(int argc, char** argv){
    std::ofstream output("../resources/output.txt");
    try {
        if (argc > 1) {
            auto papers = ReadPapersReviews(argv[1]);


            //write dataset:
            {
                //Create a file object where we will write our dataset, as follows:
                
                HighFive::File file(file_name, HighFive::File::ReadWrite|
                                    HighFive::File::Create |
                                    HighFive::File::Truncate);



                //After we have a file object, we can start creating groups. We define a 
                //group of papers that should hold all paper objects, as follows:
                auto papers_group = file.createGroup("papers");



                //Then, we iterate through an array of papers (as shown in the previous section) and
                //create a group for each paper object with two attributes: the numerical id attribute and the
                //preliminary_decision attribute of the string type, as illustrated in the following code block:
                for (const auto& paper : papers) {
                    auto paper_group = 
                       papers_group.createGroup("paper_" + std::to_string(paper.id));
                    std::vector<uint32_t> id = {paper.id};
                    auto id_attr = paper_group.createAttribute<uint32_t>(
                        "id" , HighFive::DataSpace::From(id));

                id_attr.write(id);
                auto dec_attr = paper_group.createAttribute<std::string>(
                    "preliminary_decision",
                    HighFive::DataSpace::From(paper.preliminary_decision));
                //After we have created an attribute, we have to put in its value with
                // the write() method. Note that the HighFive::DataSpace::From function automatically
                // detects the size of the attribute value. The size is the amount of memory required to hold
                // the attribute's value. 
                dec_attr.write(paper.preliminary_decision);


                // Then, for each paper_group, we create a corresponding group of reviews, as follows:
                auto reviews_group = paper_group.createGroup("reviews");



                //We insert into each reviews_group a dataset of numerical values of confidence, evaluation, and orientation fields.
                // For the dataset, we define the DataSpace(the number of elements in the dataset) of size 3 and define a storage type
                // as a 32-bit integer, as follows:
                std::vector<size_t> dims = {3};
                std::vector<int32_t> values(3);


                /*
                After we have created and initialized all objects, the Papers/Reviews dataset in HDF5
                format is ready. When the file object leaves the scope, its destructor saves everything
                to the secondary storage.

                Having the file in the HDF5 format, we can consider the HighFive library interface for file
                reading. As the first step, we again create the HighFive::File object, but with attributes for reading,
                as follows: 
                */
                for (const auto& r: paper.reviews){
                    auto dataset = reviews_group.createDataSet<int32_t>(
                        std::to_string(r.id), HighFive::DataSpace(dims));
                    values[0] = std::stoi(r.confidence);
                    values[1] = std::stoi(r.evaluation);
                    values[2] = std::stoi(r.orientation);
                    dataset.write(values);
                }
                
                }
            }

            //read dataset
            {
              /*
              After we have created an attribute, we have to put in its value with the write() method.
              Notice that the HighFive::DataSpace::From function automatically detects the size of the
              attribute value. The size is the amount of memory required to hold the attribute's value.
              */
             //Having the file in the HDF5 format, we can consider the HighFive library interface for file
             // reading. As the first step, we again create the HighFive::File object, but with attributes 
             // for reading, as follows:
              HighFive::File file(file_name, HighFive::File::ReadOnly);


              //Then, we use the getGroup() method to get the top-level papers_group object, as follows:
              auto papers_group = file.getGroup("papers");

              //We need to get a list of all nested objects in the group because we can access objects only by their names.
              //We can do this by running the following code: 
              auto papers_names = papers_group.listObjectNames();

              //For each paper object, we read its attributes, and the memory space required for the attribute value.
              //Also, because each attribute can be multidimensional, we should take care of it and allocate an
              //appropriate container, as follows:
              for (const auto& pname : papers_names) {
                  auto paper_group = papers_group.getGroup(pname);
                  std::vector<uint32_t> id;
                  paper_group.getAttribute("id").read(id);
                  output << id[0];

                  std::string decision;
                  paper_group.getAttribute("preliminary_decision").read(decision);
                  output << " " << decision << std::endl;



                  //For reading datasets, we can use the same approach: get the reviews group, then get
                  //a list of dataset names, and finally, read each dataset in a loop, as follows:
                  auto reviews_group = paper_group.getGroup("reviews");
                  auto reviews_names = reviews_group.listObjectNames();
                  std::vector<int32_t> values(2);
                  for (const auto& rname : reviews_names){
                      output << "\t review: " << rname << std::endl;
                      auto dataset = reviews_group.getDataSet(rname);
                      auto selection = dataset.select(
                          {1},{2} // or use just dataset.read method to get whole data
                      );
                      selection.read(values);
                      output << "\t\t evaluation: " << values[0] << std::endl;
                      output << "\t\t orientation: " << values[1] << std::endl;   
                
            }
        }
    }
} else {
    std::cerr << "Please provide the path to the dataset \n";
 }
} catch(const std::exception& err){
    std::cerr << err.what() << std::endl;
}

return 0;
}

/*
Notice that we use the select() method for the dataset, which allows us to read only a part of the 
dataset. We define this part with ranges given as arguments. There is the read() method in the dataset
type to read a whole dataset at once.


Using these techniques, we can read and transform any HDF5 datasets. This file format allows us to work only with
part of the required data and not to load the whole file to the memory. Also, because this is a binary format, its 
reading is more efficient than reading large text files.
*/