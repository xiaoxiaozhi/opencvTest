#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("D:/images/test5.png");
	if (src.empty()) {
		printf("could not find image file");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	
	vector<Mat> mv;
	split(src, mv);
	int size = mv.size();
	printf("number of channels : %d \n", size);
	imshow("blue channel", mv[0]);
	imshow("green channel", mv[1]);
	imshow("red channel", mv[2]);
	bitwise_not(mv[0], mv[0]);
	Mat dst;
	merge(mv, dst);
	imshow("result", dst);

	// ROI
	Rect roi;
	roi.x = 100;
	roi.y = 100;
	roi.width = 250;
	roi.height = 200;
	Mat sub = src(roi).clone();
	bitwise_not(sub, sub);
	rectangle(src, roi, Scalar(255, 255, 0), 1, 8);
	imshow("roi", sub);
	imshow("input", src);
	waitKey(0);
	destroyAllWindows();
	return 0;
}
