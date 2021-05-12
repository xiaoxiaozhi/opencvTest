#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("D:/zhigang/opencv4_images/test.png");
	if (src.empty()) {
		printf("could not find image file");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	Mat dst;
	Laplacian(src, dst, -1, 3, 1.0, 0, BORDER_DEFAULT);
	imshow("laplacian demo", dst);

	// Èñ»¯
	Mat sh_op = (Mat_<int>(3, 3) << 0, -1, 0, 
														-1, 5, -1, 
														0, -1, 0);

	Mat result;
	filter2D(src, result, CV_32F, sh_op, Point(-1, -1), 0, BORDER_DEFAULT);
	convertScaleAbs(result, result);
	imshow("sharpen filter", result);
	
	waitKey(0);
	destroyAllWindows();
	return 0;
}
