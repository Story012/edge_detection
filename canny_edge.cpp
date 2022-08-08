#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

cv::Mat src, src_gray;
cv::Mat dst, detected_edges;
int threshold1 = 0;
const int max_threshold1 = 2000;
int threshold2 = 0;
const int max_threshold2 = 2000;
const int ratio = 3;
const int kernel_size = 5;
const char* window_name = "Edge Map";
static void CannyThreshold(int, void*)
{
    cv::blur( src_gray, detected_edges, cv::Size(5,5) );
    cv::Canny( detected_edges, detected_edges, threshold1, threshold2, kernel_size );
    dst = cv::Scalar::all(0);
    src.copyTo( dst, detected_edges);
    cv::imshow( window_name, dst );
}
int main( int argc, char** argv )
{
    std::string image_path = "/home/sebas/Documents/minirover_ws/edge_detection/Media/Refractory_Channel.png";
    src = cv::imread(image_path, cv::IMREAD_COLOR);
    dst.create( src.size(), src.type() );
    cv::cvtColor( src, src_gray, cv::COLOR_BGR2GRAY );
    cv::namedWindow( window_name, cv::WINDOW_AUTOSIZE );
    cv::createTrackbar( "Threshold 1:", window_name, &threshold1, max_threshold1, CannyThreshold );
    cv::createTrackbar( "Threshold 2:", window_name, &threshold2, max_threshold2, CannyThreshold );
    CannyThreshold(0, 0);
    cv::waitKey(0);
    return 0;
}
// Great Threshold results for channel...
//threshold1: 420
//threshold2: 1200
