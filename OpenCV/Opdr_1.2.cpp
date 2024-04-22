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
	string path = "Resources/warp_object.png";
	Mat img = imread(path);
	Mat imgResize, imgCrop;

	 //resize
	//resize(img, imgResize, Size(640, 480));

	// scale 
	resize(img, imgResize, Size(), 0.5, 0.5);

	// croping
	Rect roi(100, 200, 300, 250);
	imgCrop = img(roi);

	imshow("Original image", img);
	imshow("Image resize", imgResize);
	imshow("Image crop", imgCrop);

	waitKey(0);

	return 0;
}