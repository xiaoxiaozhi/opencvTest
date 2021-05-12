#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("D:/images/flat.jpg");
	if (src.empty()) {
		printf("could not find image file");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	imshow("gray", gray);
	Scalar m = mean(gray);
	Mat dst;
	bilateralFilter(gray, dst, 0, 50, 10);
	imshow("bilateral denoise", dst);

	printf("means : %.2f\n", m[0]);
	threshold(dst, binary, m[0], 255, THRESH_BINARY);
	imshow("binary", binary);
	//大津法
	double t1 = threshold(dst, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("otsu binary", binary);
	//三角法
	double t2 = threshold(dst, binary, 0, 255, THRESH_BINARY | THRESH_TRIANGLE);
	imshow("triangle binary", binary);

	printf("otsu theshold 阈值: %.2f, triangle threshold 阈值: %.2f \n", t1, t2);

	adaptiveThreshold(dst, binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 25, 10);
	imshow("ada-binary", binary);

	waitKey(0);
	destroyAllWindows();
	return 0;
}
