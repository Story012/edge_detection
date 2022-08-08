#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int main()
{
    std::string image_path = "/home/robotics/projects/vision/build/image8.png";
    Mat img = imread(image_path, IMREAD_COLOR);

	std::cout << "Width : " << img.cols << std::endl;
	std::cout << "Height: " << img.rows << std::endl;
    
    if(img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    imshow("Display window", img);
    int k = waitKey(0); // Wait for a keystroke in the window
    if(k == 's')
    {
        imwrite("image2.jpg", img);
    }
    return 0;
}
