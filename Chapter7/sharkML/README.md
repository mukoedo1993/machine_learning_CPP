'''
rm -r build
#rm -r results
mkdir build && mkdir results && cd build
cmake ..; cmake --build . --config Release
./sharkml_classify ../../data
'''
# #