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

int main()
{
	//new image with size, 8bit unsigned 3 color channels, color
	Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255));

	circle(img, Point(256, 256), 155, Scalar(255, 0, 255), 10);
	rectangle(img, Point(128, 128), Point(380, 380), Scalar(0, 0, 0), 3);
	line(img, Point(0, 0), Point(512, 512), Scalar(50, 50, 50), 3);
	line(img, Point(0, 512), Point(512, 0), Scalar(50, 50, 50), 3);
	putText(img, "De nieuwe Vincent van Gogh", Point(30, 450), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 255), 2);

	imshow("Vincent van Gogh", img);
	waitKey(0);
}
