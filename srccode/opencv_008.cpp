#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
void eh_demo();
void hist_compare();
int main(int argc, char** argv) {
	hist_compare();
	/*Mat src = imread("D:/images/gray.png");
	if (src.empty()) {
		printf("could not find image file");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);
	vector<Mat> mv;
	split(src, mv);

	// 计算直方图
	int histSize = 256;
	Mat b_hist, g_hist, r_hist;
	float range[] = { 0, 255 };
	const float* histRanges = { range };
	calcHist(&mv[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRanges, true, false);
	calcHist(&mv[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRanges, true, false);
	calcHist(&mv[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRanges, true, false);

	Mat result = Mat::zeros(Size(600, 400), CV_8UC3);
	int margin = 50;
	int nm = result.rows - 2*margin;
	normalize(b_hist, b_hist, 0, nm, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, nm, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, nm, NORM_MINMAX, -1, Mat());
	float step = 500.0 / 256.0;
	for (int i = 0; i < 255; i++) {
		line(result, Point(step*i+50, 50 + (nm - b_hist.at<float>(i, 0))), Point(step*(i + 1)+50, 50 + (nm - b_hist.at<float>(i + 1, 0))), Scalar(255, 0, 0), 2, 8, 0);
		line(result, Point(step*i+50, 50 + (nm - g_hist.at<float>(i, 0))), Point(step*(i + 1)+50, 50 + (nm - g_hist.at<float>(i + 1, 0))), Scalar(0, 255, 0), 2, 8, 0);
		line(result, Point(step*i+50, 50 + (nm - r_hist.at<float>(i, 0))), Point(step*(i + 1)+50, 50 + (nm - r_hist.at<float>(i + 1, 0))), Scalar(0, 0, 255), 2, 8, 0);
	}
	imshow("histgorm-demo", result);
	*/
	waitKey(0);
	destroyAllWindows();
	return 0;
}

void eh_demo() {
	Mat src = imread("D:/images/gray.png");
	Mat gray, dst;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	imshow("gray", gray);
	equalizeHist(gray, dst);
	imshow("eh-demo", dst);

	// 计算直方图
	int histSize = 256;
	Mat b_hist, g_hist, r_hist;
	float range[] = { 0, 255 };
	const float* histRanges = { range };
	calcHist(&gray, 1, 0, Mat(), b_hist, 1, &histSize, &histRanges, true, false);
	calcHist(&dst, 1, 0, Mat(), g_hist, 1, &histSize, &histRanges, true, false);

	Mat result = Mat::zeros(Size(600, 400), CV_8UC3);
	int margin = 50;
	int nm = result.rows - 2 * margin;
	normalize(b_hist, b_hist, 0, nm, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, nm, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, nm, NORM_MINMAX, -1, Mat());
	float step = 500.0 / 256.0;
	for (int i = 0; i < 255; i++) {
		line(result, Point(step*i + 50, 50 + (nm - g_hist.at<float>(i, 0))), Point(step*(i + 1) + 50, 50 + (nm - g_hist.at<float>(i + 1, 0))), Scalar(0, 255, 255), 2, 8, 0);
		line(result, Point(step*i + 50, 50 + (nm - b_hist.at<float>(i, 0))), Point(step*(i + 1) + 50, 50 + (nm - b_hist.at<float>(i + 1, 0))), Scalar(0, 0, 255), 2, 8, 0);
	}
	imshow("result", result);
}

void hist_compare() {
	Mat src1 = imread("D:/images/cat.jpg");
	Mat src2 = imread("D:/images/flower.png");
	imshow("input1", src1);
	imshow("input2", src2);
	int histSize[] = { 256, 256, 256 };
	int channels[] = { 0, 1, 2 };
	Mat hist1, hist2;
	float c1[] = { 0, 255 };
	float c2[] = { 0, 255 };
	float c3[] = { 0, 255 };
	const float* histRanges[] = { c1, c2, c3 };
	calcHist(&src1, 1, channels, Mat(), hist1, 3, histSize, histRanges, true, false);
	calcHist(&src2, 1, channels, Mat(), hist2, 3, histSize, histRanges, true, false);

	// 归一化
	normalize(hist1, hist1, 0, 1.0, NORM_MINMAX, -1, Mat());
	normalize(hist2, hist2, 0, 1.0, NORM_MINMAX, -1, Mat());

	// 比较巴氏距离
	double h12 = compareHist(hist1, hist2, HISTCMP_BHATTACHARYYA);
	double h11 = compareHist(hist1, hist1, HISTCMP_BHATTACHARYYA);
	printf("h12 : %.2f, h11 : %.2f\n", h12, h11);

	// 相关性比较
	double c12 = compareHist(hist1, hist2, HISTCMP_CORREL);
	double c11 = compareHist(hist1, hist1, HISTCMP_CORREL);
	printf("c12 : %.2f, c11 : %.2f\n", c12, c11);
}