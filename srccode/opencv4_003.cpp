#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	/*
	Mat src1 = imread("D:/opencv_4.1.0/opencv/sources/samples/data/WindowsLogo.jpg");
	Mat src2 = imread("D:/opencv_4.1.0/opencv/sources/samples/data/LinuxLogo.jpg");
	if (src1.empty() || src2.empty()) {
		printf("could not find image file");
		return -1;
	}
	imshow("input1", src1);
	imshow("input2", src2);

	// ДњТыбнЪО
	Mat dst1;
	add(src1, src2, dst1);
	imshow("add-demo", dst1);

	Mat dst2;
	subtract(src1, src2, dst2);
	imshow("subtract-demo", dst2);

	Mat dst3;
	multiply(src1, src2, dst3);
	imshow("multiply-demo", dst3);

	Mat dst4;
	divide(src1, src2, dst4);
	imshow("divide-demo", dst4);
	*/
	Mat src = imread("D:/images/flower.png");
	imshow("input", src);
	Mat black = Mat::zeros(src.size(), src.type());
	black = Scalar(127, 127, 127);
	Mat dst;
	subtract(src, black, dst);
	imshow("result", dst);

	Mat dst2;
	addWeighted(src, 0.5, black, 0.5, 0.0, dst2);
	imshow("dst2", dst2);

	waitKey(0);
	destroyAllWindows();
	return 0;
}
