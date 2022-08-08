#include "opencv2/opencv.hpp"

using namespace cv;

int main(int, char**)
{
//VideoCapture cap(0); // open the default camera
VideoCapture cap("/home/sebas/Desktop/vision/Media/Minirover.mp4"); // open the video file
if(!cap.isOpened())  // check if we succeeded
    return -1;

namedWindow("Video",1);
for(;;)
{
    Mat frame;
    cap >> frame; // get a new frame from camera        
    imshow("Video", frame);
    if(waitKey(30) >= 0) break;
}
// the camera will be deinitialized automatically in VideoCapture destructor
return 0;
}
