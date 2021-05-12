#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void add_salt_and_pepper_noise(Mat &image);
void add_gaussian_noise(Mat &image);
int main(int argc, char** argv) {
	Mat src = imread("D:/zhigang/opencv4_images/t1.jpg");
	if (src.empty()) {
		printf("could not find image file");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);
	// add_gaussian_noise(src);
	/*
	// 中值滤波
	Mat dst;
	medianBlur(src, dst, 5);
	imshow("median denoise demo", dst);

	// 高斯滤波
	GaussianBlur(src, dst, Size(5, 5), 0);
	imshow("gaussian denoise demo", dst);
	*/
	// 双边
	Mat dst;
	bilateralFilter(src, dst, 0, 50, 10);
	imshow("bilateral denoise", dst);

	Mat gray, result2;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	// fastNlMeansDenoisingColored(src, dst, 3., 3., 7, 21);
	// imshow("NLM denoise", dst);
	// fastNlMeansDenoising(gray, result2, 15, 10, 30);
	// imshow("NLM denoise", result2);

	waitKey(0);
	destroyAllWindows();
	return 0;
}

void add_salt_and_pepper_noise(Mat &image) {
	// salt and pepper
	RNG rng(12345);
	int h = image.rows;
	int w = image.cols;
	int nums = 10000;
	for (int i = 0; i < nums; i++) {
		int x = rng.uniform(0, w);
		int y = rng.uniform(0, h);
		if (i % 2 == 1) {
			image.at<Vec3b>(y, x) = Vec3b(255, 255, 255);
		}
		else {
			image.at<Vec3b>(y, x) = Vec3b(0, 0, 0);
		}
	}
	imshow("salt and pepper noise", image);
}

void add_gaussian_noise(Mat &image) {
	// 高斯噪声
	Mat noise = Mat::zeros(image.size(), image.type());
	randn(noise, Scalar(25, 15, 45), Scalar(60, 40, 30));
	imshow("noise", noise);
	Mat dst;
	add(image, noise, dst);
	imshow("gaussian noise", dst);
	dst.copyTo(image);
}
