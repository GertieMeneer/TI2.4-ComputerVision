#ifdef _DEBUG
#pragma comment(lib, "opencv_world470d.lib")
#else
#pragma comment(lib, "opencv_world470.lib")
#endif

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/bgsegm.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// Function to preprocess the plate image and extract characters
vector<Rect> detectCharacters(const Mat& plate) {
    Mat gray, blurred, thresh, morph;
    vector<Rect> charBoxes;

    // Convert to grayscale
    cvtColor(plate, gray, COLOR_BGR2GRAY);

    // Apply GaussianBlur to reduce noise
    GaussianBlur(gray, blurred, Size(3, 3), 0);

    // Apply adaptive thresholding
    adaptiveThreshold(blurred, thresh, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 11, 2);

    // Apply morphological operations to separate characters better
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    morphologyEx(thresh, morph, MORPH_CLOSE, kernel);

    // Find contours
    vector<vector<Point>> contours;
    findContours(morph, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // Filter contours and find bounding boxes for characters
    for (const auto& contour : contours) {
        Rect bbox = boundingRect(contour);
        if (bbox.height > 20 && bbox.width > 10 && bbox.height > bbox.width) { // Filtering based on size
            charBoxes.push_back(bbox);
        }
    }

    return charBoxes;
}

int main() {
    VideoCapture cap(0);
    Mat img;

    // Initialize the background subtractor
    Ptr<BackgroundSubtractor> bgSubtractor = bgsegm::createBackgroundSubtractorMOG();

    CascadeClassifier plateCascade;
    plateCascade.load("Resources/haarcascade_russian_plate_number.xml");

    if (plateCascade.empty()) {
        cout << "XML file not loaded" << endl;
        return -1;
    }

    vector<Rect> plates;

    while (true) {
        cap.read(img);

        // Apply background subtraction
        Mat fgMask;
        bgSubtractor->apply(img, fgMask);

        // Find contours in the foreground mask
        vector<vector<Point>> contours;
        findContours(fgMask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        // Draw contours on the original image for visualization
        for (size_t i = 0; i < contours.size(); i++) {
            drawContours(img, contours, (int)i, Scalar(0, 255, 0), 2);
        }

        plateCascade.detectMultiScale(img, plates, 1.1, 10);

        for (int i = 0; i < plates.size(); i++) {
            Mat imgCrop = img(plates[i]);
            imwrite("Resources/Plates/plate_" + to_string(i) + ".png", imgCrop);

            vector<Rect> charBoxes = detectCharacters(imgCrop);

            // Save each character
            for (int j = 0; j < charBoxes.size(); j++) {
                Rect charBox = charBoxes[j];
                Mat charImg = imgCrop(charBox);
                imwrite("Resources/Plates/plate_" + to_string(i) + "_char_" + to_string(j) + ".png", charImg);

                // Draw rectangle around each character
                rectangle(imgCrop, charBox.tl(), charBox.br(), Scalar(0, 255, 0), 2);
            }

            rectangle(img, plates[i].tl(), plates[i].br(), Scalar(255, 0, 255), 3);
        }

        imshow("Image", img);
        if (waitKey(1) == 27) { // Break the loop if 'ESC' is pressed
            break;
        }
    }

    return 0;
}
