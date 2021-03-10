#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/image_transforms.h>

#include <experimental/filesystem>
#include <iostream>


namespace fs = std::experimental::filesystem;


int main(int argc, char** argv){
    using namespace dlib;



    /*
    The dlib::array2d type is a template type that has to be parameterized with a 
    pixel type.
    Pixel types in the dlib library are defined with pixel-type traits. There are following
    predefined pixel types:
    rgb_pixel, bgr_pixel, rgb_alpha_pixel, hsi_pixel, lab_pixel, and any scalar type can be used
    for the grayscaled pixels' representation.
    */
    array2d<rgb_pixel> img;
    try {
       if (argc > 1){
           if (fs::exists(argv[1])){
               //Use load_image(...,...) fcn. to load an image from disk, as follows:
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
    /*
    For a scaling operation, there is the dlib::resize_image() fcn. . This function has
    two different overloads. One takes a single scale factor and a reference to an image object.
    The second one takes an input image, an output image, the desired size, and an interpolation type.
    To speicify the interpolation type in the dlib library, we should call special functions:
    the interpolate_nearest_neighbor(), the interpolate_quadratic(), and the interpolate_bilinear() fcn.
    
    */
    resize_image(img, img2, interpolate_nearest_neighbor()/*ctor. to make a temp. object here*/);
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


        save_jpeg(img, "../resources/img.jpeg");
        save_jpeg(img2, "../resources/img2.jpeg");
        save_jpeg(img_bgr, "../resources/img_bgr.jpeg");
        save_jpeg(img_gray, "../resources/img_gray.jpeg");
        save_jpeg(img, "../resources/img_float.jpeg");
    

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