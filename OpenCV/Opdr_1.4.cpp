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

float w = 400, h = 256;
Mat matrix, imgWarp;

int main()
{
	string path = "Resources/warp_object.png";
	Mat img = imread(path);

	//source points to be warped
	Point2f src[4] = { {148, 302}, {286, 226}, {212, 402}, {365, 308} };

	//destination points
	Point2f dst[4] = { {0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h} };

	matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarp, matrix, Point(w, h));


	imshow("Warp Object", img);
	imshow("Warp Object", imgWarp);
	waitKey(0);
}
