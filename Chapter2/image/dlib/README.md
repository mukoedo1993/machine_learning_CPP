# TARGET:
Use Dlib library to read the image file.

```
#Ubuntu terminal:
rm -rf build; rm -rf resources; mkdir build && cd build && cmake ..; cmake --build . --config Release
#Wait for a few minutes for the make command to finish.
#Copy the data.csv into the build directory.
#Run:
mkdir ../resources; ./linalg_dlib ../../opencv/resources/cards.jpg
```