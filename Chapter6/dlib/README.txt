rm -r build && rm -r ../results
mkdir build && mkdir ../results && cd build && cmake ..; cmake --build . --config Release
#Wait for a few minutes for the make command to finish.
#Run:
./dlib_dr1 ../../data #LINE 7
# Then, just follow the instructions.
# Check the dlib/results directory.
#On the terminal, Original data size 262144
# New data size 45760 should be printed out.