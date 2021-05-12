#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("D:/images/master.jpg");
	if (src.empty()) {
		printf("could not find image file");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	// 图像取反
	Mat m1;
	Mat mask = Mat::zeros(src.size(), CV_8UC1);
	Mat mask2 = Mat::zeros(src.size(), CV_8UC1);
	int w = src.cols/2;
	int h = src.rows / 2;
	for (int row = 50; row < h; row++) {
		for (int col = 100; col < w+100; col++) {
			mask.at<uchar>(row, col) = 127;
			mask2.at<uchar>(row, col) =0;
		}
	}
	imshow("mask", mask);
	imshow("mask2", mask2);
	bitwise_not(src, m1, mask);
	imshow("bitwise not", m1);

	// 与操作
	Mat m2;
	bitwise_and(src, src, m2, mask2);
	imshow("bitwise and", m2);

	// 或操作
	Mat m3;
	bitwise_or(mask, mask2, m3);
	imshow("bitwise or", m3);

	waitKey(0);
	destroyAllWindows();
	return 0;
}
