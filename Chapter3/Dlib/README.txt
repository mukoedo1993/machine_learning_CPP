# Cross validation training in this small probject here.

#Ubuntu terminal: 
rm -r build
mkdir build && cd build && cmake ..; cmake --build . --config Release
#Wait for a few minutes for the make command to finish.
#Copy the data.csv into the build directory.
#Run:
./grid_dlib