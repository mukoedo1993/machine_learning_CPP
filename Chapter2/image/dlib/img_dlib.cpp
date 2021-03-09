#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/image_transforms.h>

#include <experimental/filesystem>
#include <iostream>


namespace fs = std::experimental::filesystem;


int main(int argc, char** argv){
    using namespace dlib;
    array2d<rgb_pixel> img;
    try {
       if (argc > 1){
           if (fs::exists(argv[1])){
               load_image(img, argv[1]);
           } else {
               std::cerr << "Invalid file path " << argv[1] << std::endl;
               return 1;
           }
       } else {
           long width = 512;
           img.set_size(width, width);
           assign_all_pixels(img, rgb_pixel(255, 255, 255));
           fill_rect(
               img,
               rectangle(img.nc() / 4, img.nr() / 4, img.nc() /2, img.nr() /2) ,
               rgb_pixel(0, 0, 0));  
       }
       unsigned long key;
       bool is_printable;
       //show original image
       image_window window(img, "Image");
       window.get_next_keypress(key, is_printable);

           // sacle
    array2d<rgb_pixel> img2(img.nr() / 2, img.nc() / 2);
    // there are also other interpolation methods interpolate_quadratic() and 
    // interpolate_bilinear
    resize_image(img, img2, interpolate_nearest_neighbor());
    std::swap(img, img2);
    window.set_image(img);
    window.get_next_keypress(key, is_printable);
    

    int top = 50;   // px
    int bottom = 20;    // px
    int left = 150;     // px
    int right = 5;      // px
    img2.set_size(img.nr() + top + bottom, img.nc() + left + right);
    transform_image(
        img, img2, interpolate_bilinear(),
        point_transform_affine(identity_matrix<double>(2),
                              dlib::vector<double, 2>(-left / 2, -top / 2)));

        std::swap(img, img2);
        window.set_image(img);
        window.get_next_keypress(key, is_printable);

        // Convert from default BGR to rgb
        array2d<bgr_pixel> img_bgr;
        assign_image(img_bgr, img);

        // Make grayscale
        array2d<unsigned char> img_gray;
        assign_image(img_gray, img);

        // Change underlying data type
        array2d<float> img_float;
        assign_image(img_float, img);

        // Mix layers
        // There are no special functions in dlib to manipulate channels
        // but we can access raw data with image_data function and get row padding
        // with width_step. Pixels stored in row major order with interleaved 
        // channels or do simple loop over all pixels
        array2d<rgb_pixel> rgb_img(5, 5);
        assign_all_pixels(rgb_img, rgb_pixel(255, 128, 64));
        auto channel_size = static_cast<size_t> (rgb_img.nc() * rgb_img.nr());
        std::vector <unsigned char> ch1(channel_size);
        std::vector <unsigned char> ch2(channel_size);
        std::vector <unsigned char> ch3(channel_size);
        size_t i{0};
        for (long r = 0; r < rgb_img.nr(); ++r){
            for (long c = 0; c < rgb_img.nc(); ++c){
                ch1[i] = rgb_img[r][c].red;
                ch2[i] = rgb_img[r][c].green;
                ch3[i] = rgb_img[r][c].blue;
                ++i;
            }
        }
    } catch (const std::exception& err){
        std::cerr << err.what();
    }


    
    return 0;
}