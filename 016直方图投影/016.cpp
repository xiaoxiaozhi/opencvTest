#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat model = imread("D:/images/flat.jpg");
	Mat src = imread("D:/images/flat_part.jpg");
	if (src.empty() || model.empty()) {
		printf("could not find image files");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);
	imshow("sample", model);

	Mat model_hsv, image_hsv;
	cvtColor(model, image_hsv, COLOR_BGR2HSV);
	cvtColor(src, model_hsv, COLOR_BGR2HSV);

	int h_bins = 48, s_bins = 48;
	int histSize[] = { h_bins, s_bins };
	int channels[] = { 0, 1 };
	Mat roiHist;
	float h_range[] = { 11, 25 };
	float s_range[] = { 43, 255 };
	const float* ranges[] = { h_range, s_range };
	calcHist(&model_hsv, 1, channels, Mat(), roiHist, 2, histSize, ranges, true, false);
	normalize(roiHist, roiHist, 0, 255, NORM_MINMAX, -1, Mat());
	MatND backproj;
	calcBackProject(&image_hsv, 1, channels, roiHist, backproj, ranges, 1.0);
	imshow("back projection demo", backproj);

	waitKey(0);
	destroyAllWindows();
	return 0;
}
