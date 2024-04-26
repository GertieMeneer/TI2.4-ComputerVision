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

int main() {
    string path = "Resources/ballstripes.jpg";
    Mat img = imread(path);
    Mat result;

    dilate(img, result, Mat(), Point(-1, -1), 5);

    imshow("Image", img);
    imshow("Result", result);

    waitKey(0);
    return 0;
}
