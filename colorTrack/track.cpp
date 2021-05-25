#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	/*
	//VideoCapture capture("D:/images/121759.mp4"); 
	VideoCapture capture("D:/images/0426000600004.mp4");
	if (!capture.isOpened()) {
		printf("could not open the camera...\n");
		return -1;
	}
	namedWindow("frame", WINDOW_AUTOSIZE);

	Mat frame, ycrcb, hsv, mask, result;
	while (true) {
		bool ret = capture.read(frame);
		if (!ret) break;

		/*cvtColor(frame, ycrcb, COLOR_BGR2YCrCb);
		//imshow("ycrcb", ycrcb);
		// Split image into channels
		vector<Mat> channels;
		split(ycrcb, channels);

		// Equalize the Y channel only
		equalizeHist(channels[0], channels[0]);

		// Merge the result channels
		merge(channels, ycrcb);
		// Show image
		//imshow("Equalized", ycrcb);
		// Convert color ycrcb to BGR
		cvtColor(ycrcb, hsv, COLOR_YCrCb2BGR);

		imshow("bgr", hsv);
		cvtColor(hsv, hsv, COLOR_BGR2HSV);
		// Show image--
		//imshow("hsv", hsv);

		cvtColor(frame, hsv, COLOR_BGR2HSV);
		inRange(hsv, Scalar(11, 43, 46), Scalar(25, 255, 255), mask);//提取指定颜色 输出到mask
		bitwise_not(mask, mask);
		bitwise_and(frame, frame, result, mask);

		imshow("mask", mask);
		//imshow("result", result);
		char c = waitKey(5);
		if (c == 27) { // ESC
			break;
		}
	}
	capture.release();*/

	VideoCapture capture("D:/images/0426000600004.mp4");
	if (!capture.isOpened()) {
		printf("could not open the camera...\n");
		return -1;
	}
	namedWindow("frame", WINDOW_AUTOSIZE);

	Mat frame, hsv, mask, result;
	while (true) {
		bool ret = capture.read(frame);
		if (!ret) break;
		imshow("frame", frame);
		cvtColor(frame, hsv, COLOR_BGR2HSV);
		imshow("hsv", hsv);
		inRange(hsv, Scalar(11, 43, 46), Scalar(25, 255, 255), mask);
		//cout << "L= (C)" << endl << format(mask, Formatter::FMT_C) << endl << endl;
		//bitwise_not(mask, mask);// 黑白互换
		//bitwise_and(frame, frame, result, mask);
		imshow("mask", mask);
		//imshow("result", result);
		char c = waitKey(5);
		if (c == 27) { // ESC
			break;
		}
	}
	capture.release();
	waitKey(0);
	destroyAllWindows();
}