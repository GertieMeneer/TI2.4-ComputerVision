#ifdef _DEBUG
#pragma comment ( lib, "opencv_world470d.lib" )
#else
#pragma comment ( lib, "opencv_world470.lib" )
#endif

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int lowThreshold = 0;
int highThreshold = 80;

void onTrackbar(int, void* userdata) {
    Mat imgBlur, imgCanny;
    Mat img = *((Mat*)userdata);

    GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);
    Canny(imgBlur, imgCanny, lowThreshold, highThreshold);
    imshow("Image Canny", imgCanny);
}

int main() {
    string path = "Resources/cat.png";
    Mat img = imread(path);
    Mat imgGray;

    cvtColor(img, imgGray, COLOR_BGR2GRAY);

    String winName = "Canny Parameters";
    namedWindow(winName);

    createTrackbar("Low Threshold", winName, &lowThreshold, 255, onTrackbar, &img);
    createTrackbar("High Threshold", winName, &highThreshold, 255, onTrackbar, &img);

    // Initial call to onTrackbar to perform Canny with default values
    onTrackbar(0, &img);

    waitKey(0);
    return 0;
}
