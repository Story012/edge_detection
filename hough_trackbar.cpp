#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

const char* hough_prob = "Hough Probabilistic";
const char* canny_blur = "Canny Filter";

int rhoP = 1;
int thetaP = CV_PI/180;
int threshP = 50;
int minLineP = 50;
int maxGapP = 10;

const int max_rhoP = 1000;
const int max_thetaP = 180;
const int max_threshP = 1000;
const int max_minLineP = 1000;
const int max_maxGapP = 1000;

cv::Mat dst, cdstP, src, src_gray, detected_edges;
std::vector<cv::Vec4i> linesP;

static void houghProb(int, void*)
{
    cv::HoughLinesP(detected_edges, linesP, rhoP, thetaP, threshP, minLineP, maxGapP);
    for( size_t i = 0; i < linesP.size(); i++ )
    {
        cv::Vec4i l = linesP[i];
        cv::line( src, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0,0,255), 3, cv::LINE_AA);
    }
    cv::imshow(hough_prob, src);
}

int main(int argc, char** argv)
{
    std::string image_path = "/home/sebas/Documents/minirover_ws/edge_detection/Media/Refractory_Channel.png";
    src = cv::imread(image_path, cv::IMREAD_COLOR);
    // Cropping to cut edges of noisy video
    src = src(cv::Range(80,1000),cv::Range(300,1620));
    cv::cvtColor( src, src_gray, cv::COLOR_BGR2GRAY );
    cv::blur( src_gray, detected_edges, cv::Size(5,5) );
    cv::Canny( detected_edges, detected_edges, 420, 1200, 5);
    cv::imshow( canny_blur, detected_edges );
    
    cv::namedWindow( hough_prob, cv::WINDOW_AUTOSIZE );
    cv::createTrackbar( "Rho:", hough_prob, &rhoP, max_rhoP, houghProb );
    cv::createTrackbar( "Theta:", hough_prob, &thetaP, max_thetaP, houghProb );
    cv::createTrackbar( "Threshold:", hough_prob, &threshP, max_threshP, houghProb );
    cv::createTrackbar( "Min Line Length:", hough_prob, &minLineP, max_minLineP, houghProb );
    cv::createTrackbar( "Max Line Gap:", hough_prob, &maxGapP, max_maxGapP, houghProb );
    
    houghProb(0,0);
    cv::waitKey();
    return 0;
}
