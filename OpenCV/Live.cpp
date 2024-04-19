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
	VideoCapture cap(0);

	Mat img;
	
	while (true) 
	{
		cap.read(img);
		imshow("Image", img);
		waitKey(50);
	}

	return 0;
}