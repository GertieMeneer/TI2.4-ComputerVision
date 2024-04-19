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
	string path = "Resources/test.png";
	Mat img = imread(path);
	Mat imgResize, imgCrop;

	cout << img.size() << endl;

	// resize
	//resize(img, imgResize, Size(640, 480));

	// scale 
	resize(img, imgResize, Size(), 0.5, 0.5);

	// croping
	Rect roi(100, 100, 300, 250);
	imgCrop = img(roi);

	/*Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);
	erode(imgDil, imgErode, kernel);*/

	imshow("Image", img);
	imshow("Image resize", imgResize);
	imshow("Image crop", imgCrop);
	/*imshow("Image Gray", imgGray);
	imshow("Image Blur", imgBlur);
	imshow("Image Canny", imgCanny);
	imshow("Image Dilation", imgDil);
	imshow("Image Erode", imgErode);*/
	waitKey(0);

	return 0;
}