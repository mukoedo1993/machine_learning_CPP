In total, five methods of clustering.See: 
std::cout << "Please input the model: Enter 1, 2, 3, 4 or 5: \n ";
std::cout<< "case(1):DoHierarhicalClustering(inputs, num_clusters, dataset)\n";
std::cout << "case(2):DoGraphClustering(inputs, dataset)\n";
std::cout << "case(3):DoKMeansClustering(inputs, num_clusters, dataset)\n";
std::cout << "case(4):DoGraphNewmanClustering(inputs, dataset)\n";
std::cout << " case(5):DoSpectralClustering(inputs, num_clusters, dataset)\n";


###
#Ubuntu terminal:
rm -r build
mkdir build && cd build && cmake ..; cmake --build . --config Release
#Wait for a few minutes for the make command to finish.
#Run:
./dlib_cluster ../data #LINE 8
# Then, just follow the instructions.
# When it is finished, you could recycle the code by running line 8 code again.