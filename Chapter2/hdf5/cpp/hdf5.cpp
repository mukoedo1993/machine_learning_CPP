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
                HighFive::File file(file_name, HighFive::File::ReadWrite|
                                    HighFive::File::Create |
                                    HighFive::File::Truncate);

                auto papers_group = file.createGroup("papers");
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
                dec_attr.write(paper.preliminary_decision);
                auto reviews_group = paper_group.createGroup("reviews");


                std::vector<size_t> dims = {3};
                std::vector<int32_t> values(3);
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
              HighFive::File file(file_name, HighFive::File::ReadOnly);
              auto papers_group = file.getGroup("papers");
              auto papers_names = papers_group.listObjectNames();
              for (const auto& pname : papers_names) {
                  auto paper_group = papers_group.getGroup(pname);
                  std::vector<uint32_t> id;
                  paper_group.getAttribute("id").read(id);
                  output << id[0];

                  std::string decision;
                  paper_group.getAttribute("preliminary_decision").read(decision);
                  output << " " << decision << std::endl;

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
