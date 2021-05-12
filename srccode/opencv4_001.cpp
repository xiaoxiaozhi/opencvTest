#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("D:/opencv_4.1.0/opencv/sources/samples/data/opencv-logo.png", IMREAD_UNCHANGED);
	if (src.empty()) {
		printf("could not find image file");
		return -1;
	}
	namedWindow("001-demo", WINDOW_AUTOSIZE);
	imshow("001-demo", src);
	imwrite("D:/testone.png", src);
	waitKey(0);
	destroyAllWindows();
	return 0;
}
