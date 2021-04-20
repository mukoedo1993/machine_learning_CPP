I am trying to implement DBSCAN algorithm on my own, with the help of dlib...
NOT FINISHED YET...


Reference:
https://en.wikipedia.org/wiki/DBSCAN
the github lib.
Hands-on ML with CPP


###
#Ubuntu terminal:
rm -r build
mkdir build && cd build && cmake ..; cmake --build . --config Release
#Wait for a few minutes for the make command to finish.
#Run:
./dlib_cluster ../data #LINE 8
# Then, just follow the instructions.
# When it is finished, you could recycle the code by running line 8 code again.
./dbscan_cluster <data file> <epsilon> <minPtrs>

