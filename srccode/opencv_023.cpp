#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
RNG rng(12345);
void ccl_stats_demo(Mat &image);
int main(int argc, char** argv) {
	Mat src = imread("D:/images/rice.png");
	if (src.empty()) {
		printf("could not find image file");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);
	GaussianBlur(src, src, Size(3, 3), 0);
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("binary", binary);
	ccl_stats_demo(binary);
	/*
	Mat labels = Mat::zeros(binary.size(), CV_32S);
	int num_labels = connectedComponents(binary, labels, 8, CV_32S, CCL_DEFAULT);
	vector<Vec3b> colorTable(num_labels);
	// backgound color
	colorTable[0] = Vec3b(0, 0, 0);
	for (int i = 1; i < num_labels; i++) {
		colorTable[i] = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
	}

	Mat result = Mat::zeros(src.size(), src.type());
	int w = result.cols;
	int h = result.rows;
	for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			int label = labels.at<int>(row, col);
			result.at<Vec3b>(row, col) = colorTable[label];
		}
	}
	putText(result, format("number: %d", num_labels - 1), Point(50, 50), FONT_HERSHEY_PLAIN, 1.0, Scalar(0, 255, 0), 1);
	printf("total labels : %d \n", (num_labels - 1));
	imshow("CCL demo", result);
	*/
	waitKey(0);
	destroyAllWindows();
	return 0;
}

void ccl_stats_demo(Mat &image) {
	Mat labels = Mat::zeros(image.size(), CV_32S);
	Mat stats, centroids;
	int num_labels = connectedComponentsWithStats(image, labels, stats, centroids, 8, CV_32S, CCL_DEFAULT);
	vector<Vec3b> colorTable(num_labels);
	// backgound color
	colorTable[0] = Vec3b(0, 0, 0);
	for (int i = 1; i < num_labels; i++) {
		colorTable[i] = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
	}

	Mat result = Mat::zeros(image.size(), CV_8UC3);
	int w = result.cols;
	int h = result.rows;
	for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			int label = labels.at<int>(row, col);
			result.at<Vec3b>(row, col) = colorTable[label];
		}
	}

	for (int i = 1; i < num_labels; i++) {
		// center
		int cx = centroids.at<double>(i, 0);
		int cy = centroids.at<double>(i, 1);
		// rectangle and area
		int x = stats.at<int>(i, CC_STAT_LEFT);
		int y = stats.at<int>(i, CC_STAT_TOP);
		int width = stats.at<int>(i, CC_STAT_WIDTH);
		int height = stats.at<int>(i, CC_STAT_HEIGHT);
		int area = stats.at<int>(i, CC_STAT_AREA);

		// ����
		circle(result, Point(cx, cy), 3, Scalar(0, 0, 255), 2, 8, 0);
		// ��Ӿ���
		Rect box(x, y, width, height);
		rectangle(result, box, Scalar(0, 255, 0), 2, 8);
		putText(result, format("%d", area), Point(x, y), FONT_HERSHEY_PLAIN, 1.0, Scalar(0, 255, 0), 1);
		
	}
	putText(result, format("number: %d", num_labels - 1), Point(10, 10), FONT_HERSHEY_PLAIN, 1.0, Scalar(0, 255, 0), 1);
	printf("total labels : %d \n", (num_labels - 1));
	imshow("CCL demo", result);
}
