#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("D:/zhigang/opencv4_images/t2.png");
	if (src.empty()) {
		printf("could not find image file");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);
	// 自定义滤波 - 均值卷积
	int k = 15;
	Mat mkernel = Mat::ones(k, k, CV_32F) / (float)(k*k);

	Mat dst;
	filter2D(src, dst, -1, mkernel, Point(-1, -1), 0, BORDER_DEFAULT);
	imshow("custom mean filter", dst);

	// 非均值滤波
	Mat robot = (Mat_<int>(2, 2) << 1, 0, 0, -1);

	Mat result;
	filter2D(src, result, CV_32F, robot, Point(-1, -1), 127, BORDER_DEFAULT);
	convertScaleAbs(result, result);
	imshow("robot filter", result);

	waitKey(0);
	destroyAllWindows();
	return 0;
}
