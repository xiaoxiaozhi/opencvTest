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

	// salt and pepper
	RNG rng(12345);
	Mat image = src.clone();
	int h = src.rows;
	int w = src.cols;
	int nums = 10000;
	for (int i = 0; i < nums; i++) {
		int x = rng.uniform(0, w);
		int y = rng.uniform(0, h);
		if (i % 2 == 1) {
			src.at<Vec3b>(y, x) = Vec3b(255, 255, 255);
		}
		else {
			src.at<Vec3b>(y, x) = Vec3b(0, 0, 0);
		}
	}
	imshow("salt and pepper noise", src);

	// ∏ﬂÀπ‘Î…˘
	Mat noise = Mat::zeros(image.size(), image.type());
	randn(noise, Scalar(25, 15, 45), Scalar(60, 40, 30));
	imshow("noise", noise);
	Mat dst;
	add(image, noise, dst);
	imshow("gaussian noise", dst);

	waitKey(0);
	destroyAllWindows();
	return 0;
}
