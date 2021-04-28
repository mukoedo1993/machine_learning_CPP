###
#Ubuntu terminal:
cd dlib
rm -r build && rm -r ../results
mkdir build && mkdir ../results && cd build && cmake ..; cmake --build . --config Release
#Wait for a few minutes for the make command to finish.
#Run:
./dlib_anomaly ../../data #LINE 7
# Then, just follow the instructions.
# When it is finished, you could recycle the code by running line 7 command  again.
