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
	int h = src.rows;
	int w = src.cols;
	Mat result = src.clone();
	for (int row = 1; row < h-1; row++) {
		for (int col = 1; col < w-1; col++) {
			// 3x3¾í»ýºË
			int sb = src.at<Vec3b>(row, col)[0] + src.at<Vec3b>(row - 1, col - 1)[0] + src.at<Vec3b>(row - 1, col)[0] +
				src.at<Vec3b>(row - 1, col + 1)[0] + src.at<Vec3b>(row, col - 1)[0] + src.at<Vec3b>(row, col + 1)[0] +
				src.at<Vec3b>(row + 1, col - 1)[0] + src.at<Vec3b>(row+1, col)[0] + src.at<Vec3b>(row+1, col + 1)[0];

			int sg = src.at<Vec3b>(row, col)[1] + src.at<Vec3b>(row - 1, col - 1)[1] + src.at<Vec3b>(row - 1, col)[1] +
				src.at<Vec3b>(row - 1, col + 1)[1] + src.at<Vec3b>(row, col - 1)[1] + src.at<Vec3b>(row, col + 1)[1] +
				src.at<Vec3b>(row + 1, col - 1)[1] + src.at<Vec3b>(row + 1, col)[1] + src.at<Vec3b>(row + 1, col + 1)[1];

			int sr = src.at<Vec3b>(row, col)[2] + src.at<Vec3b>(row - 1, col - 1)[2] + src.at<Vec3b>(row - 1, col)[2] +
				src.at<Vec3b>(row - 1, col + 1)[2] + src.at<Vec3b>(row, col - 1)[2] + src.at<Vec3b>(row, col + 1)[2] +
				src.at<Vec3b>(row + 1, col - 1)[2] + src.at<Vec3b>(row + 1, col)[2] + src.at<Vec3b>(row + 1, col + 1)[2];
			result.at<Vec3b>(row, col)[0] = sb / 9;
			result.at<Vec3b>(row, col)[1] = sg / 9;
			result.at<Vec3b>(row, col)[2] = sr / 9;
		}
	}
	imshow("conv-demo", result);
	Mat dst;
	blur(src, dst, Size(13, 13), Point(-1, -1), BORDER_DEFAULT);
	imshow("blur-demo", dst);

	// ±ßÔµÌî³ä
	int border = 8;
	Mat border_m;
	copyMakeBorder(src, border_m, border, border, border, border, BORDER_WRAP, Scalar(0, 0, 255));
	imshow("border fill demo", border_m);

	waitKey(0);
	destroyAllWindows();
	return 0;
}
