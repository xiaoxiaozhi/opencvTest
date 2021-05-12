#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("D:/images/gray.png");
	if (src.empty()) {
		printf("could not find image file");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	Mat color = imread("D:/images/lut.png");
	Mat lut = Mat::zeros(256, 1, CV_8UC3);
	for (int i = 0; i < 256; i++) {
		lut.at<Vec3b>(i, 0) = color.at<Vec3b>(10, i);
	}
	imshow("color", color);
	Mat dst;
	LUT(src, lut, dst);
	imshow("lut-demo", dst);

	applyColorMap(src, dst, COLORMAP_OCEAN);
	imshow("color-map", dst);
	waitKey(0);
	destroyAllWindows();
	return 0;
}
