#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <string>

using namespace cv;

int main(int argc, char **argv) {
    VideoCapture cap(0);   
    for (int i = 0; i <= 10; ++i) {
        std::cout << i << std::endl;
        std::cin.get();
        Mat frame; 
        cap >> frame;
        if(frame.empty())
            std::cerr << "Something is wrong with the webcam, could not get frame." << std::endl;
        std::string file("image");
        file += std::to_string(i) + ".png";
        imwrite(file, frame);
    }   
    return 0;
}
