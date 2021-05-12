#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("D:/images/t2.jpg");
	if (src.empty()) {
		printf("could not find image file");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	// robot gradient º∆À„

	Mat robot_x = (Mat_<int>(2, 2) << 1, 0, 0, -1);
	Mat robot_y = (Mat_<int>(2, 2) << 0, 1, -1, 0);

	Mat grad_x, grad_y;
	filter2D(src, grad_x, CV_32F, robot_x, Point(-1, -1), 0, BORDER_DEFAULT);
	filter2D(src, grad_y, CV_32F, robot_y, Point(-1, -1), 0, BORDER_DEFAULT);
	convertScaleAbs(grad_x, grad_x);
	convertScaleAbs(grad_y, grad_y);
	Mat result;
	add(grad_x, grad_y, result);
	imshow("robot gradient", result);


	// sobel and scharr
	Scharr(src, grad_x, CV_32F, 1, 0);
	Scharr(src, grad_y, CV_32F, 0, 1);
	convertScaleAbs(grad_x, grad_x);
	convertScaleAbs(grad_y, grad_y);
	Mat result2;
	addWeighted(grad_x, 0.5, grad_y, 0.5, 0, result2);
	imshow("sobel gradient", result2);

	waitKey(0);
	destroyAllWindows();
	return 0;
}
