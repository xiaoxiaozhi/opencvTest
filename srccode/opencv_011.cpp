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

	Mat dst;
	GaussianBlur(src, dst, Size(0, 0), 15);
	imshow("gaussina blur", dst);

	// 盒子模糊 - 均值模糊
	Mat box_dst;
	boxFilter(src, box_dst, -1, Size(25, 25), Point(-1, -1), true, BORDER_DEFAULT);
	imshow("box-blur", box_dst);
	
	waitKey(0);
	destroyAllWindows();
	return 0;
}
