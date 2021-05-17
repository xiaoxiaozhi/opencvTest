#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
void process_frame(Mat &image);
void process2(Mat &image);
auto pMOG2 = createBackgroundSubtractorMOG2(500, 100, false);
int main(int argc, char** argv) {
	VideoCapture capture("D:/images/0426000600004.mp4");
	if (!capture.isOpened()) {
		printf("could not open the camera...\n");
	}
	namedWindow("frame", WINDOW_AUTOSIZE);
	Mat frame;
	while (true) {
		bool ret = capture.read(frame);
		if (!ret) break;
		imshow("frame", frame);
		process_frame(frame);
		char c = waitKey(1);
		if (c == 27) { // ESC
			break;
		}
	}
	capture.release();

	waitKey(0);
	destroyAllWindows();
}

void process_frame(Mat &image) {
	Mat mask, bg_image;
	pMOG2->apply(image, mask);
	pMOG2->getBackgroundImage(bg_image);
	imshow("mask", mask);
	imshow("background", bg_image);
}
