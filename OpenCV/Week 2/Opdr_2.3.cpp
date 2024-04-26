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

    if (img.empty()) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    Mat imgGray, imgBlur, imgCanny, imgErode, imgDil, imgInvert;

    // 1. Convert image to grayscale
    cvtColor(img, imgGray, COLOR_BGR2GRAY);

    // 2. Apply Gaussian blur
    GaussianBlur(imgGray, imgBlur, Size(15, 15), 3, 0);

    // 3. Perform Canny edge detection
    Canny(imgBlur, imgCanny, 25, 75);

    // 4. Morphological operations (dilation and erosion)
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(imgCanny, imgDil, kernel);
    erode(imgDil, imgErode, kernel);

    // 5. Invert the image to obtain the mask for the stripes
    bitwise_not(imgErode, imgInvert);

    // 6. Apply the mask to the original image to remove the stripes
    Mat result;
    bitwise_and(img, img, result, imgInvert);

    // Display original and processed images
    imshow("Image", img);
    imshow("Result", result);

    waitKey(0);
    return 0;
}
