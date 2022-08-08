#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    // Declare the output variables
    cv::Mat dst, cdst, cdstP;
    
    std::string image_path = "/home/robotics/projects/vision/build/Refractory_Channel.png";
    cv::Mat src = cv::imread(image_path, cv::IMREAD_COLOR);
    
    std::cout << "Width : " << src.size().width << std::endl;
    std::cout << "Height: " << src.size().height << std::endl;
    std::cout << "Channels: " << src.channels() << std::endl;
    // Cropping to cut edges of noisy video
    src = src(cv::Range(80,1000),cv::Range(300,1620));
    // Edge detection
    cv::Canny(src, dst, 74, 41, 3);
    // Copy edges to the images that will display the results in BGR
    cv::cvtColor(dst, cdst, cv::COLOR_GRAY2BGR);
    cdstP = cdst.clone();
    
//     // Standard Hough Line Transform
//     std::vector<cv::Vec2f> lines; // will hold the results of the detection
//     // cv::HoughLines (image, lines, rho, theta, threshold, srn = 0, stn = 0, min_theta = 0, max_theta = Math.PI)
//     cv::HoughLines(dst, lines, 1, CV_PI/180, 150, 0, 0 ); // runs the actual detection
//     // Draw the lines
//     for( size_t i = 0; i < lines.size(); i++ )
//     {
//         float rho = lines[i][0], theta = lines[i][1];
//         cv::Point pt1, pt2;
//         double a = cos(theta), b = sin(theta);
//         double x0 = a*rho, y0 = b*rho;
//         pt1.x = cvRound(x0 + 1000*(-b));
//         pt1.y = cvRound(y0 + 1000*(a));
//         pt2.x = cvRound(x0 - 1000*(-b));
//         pt2.y = cvRound(y0 - 1000*(a));
//         cv::line( cdst, pt1, pt2, cv::Scalar(0,0,255), 3, cv::LINE_AA);
//     }
    // Probabilistic Line Transform
    std::vector<cv::Vec4i> linesP; // will hold the results of the detection
    // cv::HoughLinesP (image, lines, rho, theta, threshold, minLineLength = 0, maxLineGap = 0)
    cv::HoughLinesP(dst, linesP, 1, CV_PI/180, 50, 50, 10 ); // runs the actual detection
    // Draw the lines
    for( size_t i = 0; i < linesP.size(); i++ )
    {
        cv::Vec4i l = linesP[i];
        cv::line( cdstP, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0,0,255), 3, cv::LINE_AA);
    }
    // Show results
    cv::imshow("Source", src);
    //cv::imshow(hough_stan, cdst);
    //cv::imshow(hough_prob, cdstP);
    // Wait and Exit
    cv::waitKey();
    return 0;
}
