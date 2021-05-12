#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
void hist_compare();
int main(int arg, char** argv) {
	Mat canvas = imread("D://images/flower.png", IMREAD_COLOR);
	if (canvas.empty()) {
		printf("图像为空");
		waitKey(0);
		destroyAllWindows();
		return -1;
	}
	const double E = std::exp(1.0);
	Mat lut(1, 256, CV_8UC1);
	for (int i = 0; i<256; i++)
	{
		float x = (float)i / 256.0;
		lut.at<uchar>(i) = cvRound(256 * (1 / (1 + pow(E, -((x - 0.5) / 0.1)))));
	}

	vector<Mat> bgr;
	split(canvas, bgr);
	LUT(bgr[2], lut, bgr[2]);
	// merge result
	merge(bgr, canvas);
	imshow("canvas", canvas);

	//hist_compare();

	/*Mat result;
	add(canvas1,canvas, result);*/

	waitKey(0);
	destroyAllWindows();

}
void hist_compare() {
	Mat src1 = imread("D:/images/car.jpg");
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