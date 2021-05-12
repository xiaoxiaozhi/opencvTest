#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("D:images/car.jpg");
	if (src.empty()) {
		printf("could not find image file");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	// Unsharpen mask filter
	Mat blur_image, dst;
	GaussianBlur(src, blur_image, Size(3, 3), 0);
	Laplacian(src, dst, -1, 1, 1.0, 0, BORDER_DEFAULT);
	imshow("laplacian demo", dst);
	Mat usm_image;
	addWeighted(blur_image, 1.0, dst, -1.0, 0, usm_image);
	imshow("usm filter", usm_image);

	waitKey(0);
	destroyAllWindows();
	return 0;
}
