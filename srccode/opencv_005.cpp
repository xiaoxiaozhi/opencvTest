#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("D:/images/flower.png", IMREAD_GRAYSCALE);
	// Mat src = Mat::zeros(Size(512, 512), CV_8UC3);
	// src = Scalar(0, 0, 255);
	if (src.empty()) {
		printf("could not find image file");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);
	int w = src.cols;
	int h = src.rows;
	int ch = src.channels();
	printf("w: %d, h: %d, channels : %d \n", w, h, ch);
	// 最大最小值
	double min_val;
	double max_val;
	Point minloc;
	Point maxloc;
	minMaxLoc(src, &min_val, &max_val, &minloc, &maxloc);
	printf("min:%.2f, max: %.2f\n", min_val, max_val);
	
	// 像素值统计信息
	vector<int> hist(256);
	for (int i = 0; i < 256; i++) {
		hist[i] = 0;
	}
	for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			int pv = src.at<uchar>(row, col);
			hist[pv]++;
		}
	}
	
	// 均值方差
	/*
	Scalar s = mean(src);
	printf("mean : %.2f, %.2f, %.2f\n", s[0], s[1], s[2]);
	Mat mm, mstd;
	meanStdDev(src, mm, mstd);
	int rows = mstd.rows;
	printf("rows : %d\n", rows);
	printf("stddev : %.2f, %.2f, %.2f\n", mstd.at<double>(0, 0), mstd.at<double>(1, 0), mstd.at<double>(2, 0));
	*/
	waitKey(0);
	destroyAllWindows();
	return 0;
}
