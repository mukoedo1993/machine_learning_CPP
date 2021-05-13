'''
rm -r build
#rm -r results && mkdir results
mkdir build && cd build
cmake ..; cmake --build . --config Release
./sharkml_classify ../../data
'''
# #