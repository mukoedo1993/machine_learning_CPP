#include<opencv2/highgui.hpp>
#include<opencv2/opencv.hpp>

#include <experimental/filesystem>
#include <iostream>
#include <string>

namespace fs = std::experimental::filesystem;


/*
In the OpenCV library, an image is treated as a multidimensional matrix of values.
There is special cv::Mat type for this purpose. There are two base functions:
cv::imread() 
cv::imwrite()
*/

/*
Also, there are functions to manage images located in a memory buffer. The cv::imdecode()
function loads an image from the memory buffer, and the cv::imencode() function writes an image to
the memory buffer.
*/
int main(int argc, char** argv){
    cv::Mat img;
    if(argc > 1){
        auto file_path = fs::path(argv[1]);
        if (fs::exists(file_path)){
             img = cv::imread(file_path.string());
        } else {
            std::cerr << "File path " <<file_path << "is invalid\n";
        }
    }
    if (img.empty()){

        cv::namedWindow("Image",
                    cv::WINDOW_AUTOSIZE);   // Create a window for display
    cv::imshow("Image0", img);   //Show our image inside it.

        const int width = 512;
        img = cv::Mat(width, width, CV_32FC3);
        img = cv::Scalar(255, 255, 255);
        cv::rectangle(img, {width / 4, width / 4}, {width /2 , width /2},
        cv::Scalar(0, 0, 0),-1);
    }
   // cv::namedWindow("Image",
     //               cv::WINDOW_AUTOSIZE);   // Create a window for display
    cv::imshow("Image1", img);   //Show our image inside it.
    cv::waitKey(0);
    


    // scaling
    /*Interpolation arguments*/
    // use cv::INTER_AREA for shrinking and
    // cv::INTER_CUBIC (slow) or cv::INTER_LINEAR for zooming. By default,
    //  cv::INTER_LINEAR is used for all resizing purposes.

    cv::resize(img, img, {img.cols / 2, img.rows /2 }, 0, 0, cv::INTER_AREA);
    cv::imshow("Image2", img);
    cv::waitKey(0);//0 means the speical value: forever
    


    cv::resize(img, img, {}, 1.5, 1.5, cv::INTER_CUBIC);
    //cv::Size, the third parameter above is deducted by fourth(dx) and fifth(dy) parameters above.
    cv::imshow("Image3", img);
    cv::waitKey(0);

    //cropping: Cropping is the removal of unwanted outer areas from a photographic or illustrated image.
    /*
    There is no special function for image cropping in the opencv library, but the cv::Mat overides
    the operator() method, which takes a cropping rectangle as an argument and returns a new cv::Mat
    object with part of the image surrounded by the specified rectangle. Also, note that this object will
    share the same memory with the original image, so its modification will share the same memory with the
    original image, so its modification will change the original image too. To make a deep copy cv::Mat
    object, we need to use the clone() method, as follows:

    */
    auto img1 = img.clone();
    img = img(cv::Rect(0, 0, img.cols /2, img.rows /2));
    
    cv::imshow("Image4", img);
    cv::imshow("Image4_1", img1);
    cv::waitKey(0);

    /*
    Sometimes, we need to move or rotate an image. The opencv library supports translation 
    and rotation operations for images through affine transformationa. We have to manually --
    or with helper functions -- create a matrix of 2D affine transformations and  then apply it
    to our image. For the move(the translation), we can create such a matrix manually, and then 
    apply it to an image with the cv::wrapAffine() function:
    */
    //translation (the move):
    cv::Mat trm = (cv::Mat_<double>(2, 3) << 1, 0, -50, 0, 1, -50);
    cv::warpAffine(img, img, trm, {img.cols, img.rows});
    cv::imshow("Image5", img);
    cv::waitKey(0);


    // rotations
    /*We can create a rotation matrix with the cv::getRotationMatrix2D() function. This
    takes a point of origin and the rotation angle in degreesm as illustrated in the following code 
    snippet: */
    auto rotm = cv::getRotationMatrix2D({img.cols / 2, img.rows /2}, 45, 1);
    cv::warpAffine(img, img, rotm, {img.cols, img.rows});
    cv::imshow("Image6", img);
    cv::waitKey(0);
    /*
    cv::Mat cv::getRotationMatrix2D(cv::Point2f center, double angle, double scale)
Calculates an affine matrix of 2D rotation. The function calculates the following matrix:

Parameters:
center – Center of the rotation in the source image.
angle – Rotation angle in degrees. Positive values mean counter-clockwise rotation (the coordinate origin is assumed to be the top-left corner).
scale – Isotropic scale factor.
    */











    // padding
    // types of orders
    //BORDER_CONSTANT -single color
    //BORDER_REPLICATE - copy last values -  aaaaaa|abcdefgh|hhhhhhh
    //BORDER_REFLECT -copy opposite image values - fedcba|abcdefgh|hgfedcb
    //BORDER_WRAP simulate image duplication     cdefgh|abcdefgh|abcdefg
    //From doc: When the source is a part (ROI) of a bigger image, the function will
    //try to use the pixels outside of the ROI to form a border.
    //disable this feature and always do extrapolation, as if src was not a ROI,
    //use borderType | BORDER_ISOLATED
    int top = 50; //px
    int bottom = 20; //px
    int left = 150;  // px
    int right = 5;   //px
    cv::copyMakeBorder (img, img, top, bottom, left, right,
                        cv::BORDER_CONSTANT | cv::BORDER_ISOLATED,
                        cv::Scalar(255, 0, 0));
    
    cv::imshow("Image7", img);
    cv::waitKey(0);


    // Make grayscale
    //convert the RGB image to grayscaled one:
    cv::cvtColor (img, img,
                  cv::COLOR_RGB2GRAY);      // now pixels values are in range 0-1

    std:: cout << "Grayscale image channels " << img.channels() << std::endl;
    cv::imshow("Image8", img);
    cv::waitKey(0);

    //Change underlying data type
    img.convertTo(img, CV_8UC1, 255);// float -> byte
    cv::imshow("Image9", img);
    cv::waitKey(0);


    // Mix layers
    // layout of channels i in memory n OpenCV can be non continuous and 
    // interleaved, so usu. before passing OpenCV image to another lib. we
    // mix to restructure them.

    img = cv::Mat(512, 512, CV_32FC3);
    img = cv::Scalar(255, 255, 255);

    // To deinterleave channels, we need to split them with cv::split() function, like this:
    cv::Mat bgr[3];
    cv::split(img, bgr);
 /*
 cv::split(... , ...)
 Divides a multi-channel array into several single-channel arrays. The function cv::split splits a multi-channel array into separate single-channel arrays:

Parameters:
src – input multi-channel array.
mvbegin – output array; the number of arrays must match src.channels(); the arrays themselves are reallocated, if needed.
 */




 //It will place channel back to the cv::Mat object in the order we need with the cv::vconcat () function,
 // which concatenates matrices vertically, as follows:
    cv::Mat ordered_channels;
    cv::vconcat(bgr[2], bgr[1], ordered_channels);
    cv::vconcat(ordered_channels, bgr[0], ordered_channels);

    std::cout << "Memory layout is continuous " << ordered_channels.isContinuous()
    << std::endl;
//Grayscale image channels 1
//Memory layout is continuous 1

    return 0;



    
}