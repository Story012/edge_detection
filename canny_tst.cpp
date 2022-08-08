#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int main(int, char**)
{
    cv::VideoCapture cap("/home/sebas/Desktop/vision/Media/Minirover.mp4"); // open the video file;
    //VideoCapture cap(0);
    
    //if(!stream1.isOpened()){
    //cout << "cannot open camera" << endl;
    //}

    while (true) {
        cv::Mat blurredImage;
        cv::Mat cannyImage;
        cv::Mat cameraFrame;
        cv::Mat houghImage;
        cv::Mat cdstP;
        
        cap.read(cameraFrame);
        //imshow("Source Input", cameraFrame);

        cameraFrame = cameraFrame(cv::Range(80,1000),cv::Range(300,1620)); 
        //imshow("cropped", cameraFrame_cut);
        cdstP = cameraFrame.clone();
        cv::GaussianBlur(cameraFrame, blurredImage, cv::Size(9, 9), 0);
        //imshow("Gaussian Blur", blurredImage);
        cv::cvtColor(cameraFrame, cannyImage, cv::COLOR_BGR2GRAY);
        cv::Canny( cannyImage, cannyImage, 1396, 973, 5 );
        cv::imshow("Canny", cannyImage);
        
        std::vector<cv::Vec4i> lines;
        cv::HoughLinesP(cannyImage, lines, 1, CV_PI/180, 50, 30, 10 );
        for( size_t i = 0; i < lines.size(); i++ )
        {
        cv::Vec4i l = lines[i];
        cv::line( cdstP, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0,0,255), 3, cv::LINE_AA);
        }
        cv::imshow("Detected Lines (in red) - Probabilistic Line Transform", cdstP);

        if (cv::waitKey(30) >= 0)
            break;

        }
return 0;
}
