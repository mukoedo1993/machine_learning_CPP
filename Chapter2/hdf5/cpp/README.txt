To fix the error: sudo ln -s /usr/include/hdf5/serial/* /usr/include
Or, remember to symbolic link all files in hdf5 lib..

Read a json file, and access to the part of information we need only.

On Ubuntu:
Run:
cd build
cmake .
make
./json_sample ../resources/review.json