#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("D:/zhigang/opencv4_images/1024.jpg", IMREAD_COLOR);
	if (src.empty()) {
		printf("could not find image file");
		return -1;
	}
	namedWindow("002-demo", WINDOW_AUTOSIZE);
	imshow("002-demo", src);
	int width = src.cols;
	int height = src.rows;
	int dim = src.channels();
	int d = src.depth();
	int t = src.type();
	if (t == CV_8UC3) {
		printf("width : %d, height :%d, dim: %d, depth: %d, type: %d \n", width, height, dim, d, t);
	}

	// create one
	Mat t1 = Mat(256, 256, CV_8UC3);
	t1 = Scalar(0, 0, 255);
	imshow("t1", t1);

	// create two
	Mat t2 = Mat(Size(512, 512), CV_8UC3);
	t2 = Scalar(255, 0, 255);
	imshow("t2", t2);

	// create three
	Mat t3 = Mat::zeros(Size(256, 256), CV_8UC3);
	imshow("t3", t3);

	// create from source
	Mat t4 = src;
	Mat t5;
	src.copyTo(t5);
	t5 = Scalar(0, 0, 255);
	imshow("t5", t5);
	imshow("002-demo", src);

	Mat t6 = Mat::zeros(src.size(), src.type());
	imshow("t6", t6);

	// visit each pixel
	/*int ch = src.channels();
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			if (ch == 3) {
				Vec3b pixel = src.at<Vec3b>(row, col);
				int blue = pixel[0];
				int green = pixel[1];
				int red = pixel[2];
				src.at<Vec3b>(row, col)[0] = 255 - blue;
				src.at<Vec3b>(row, col)[1] = 255 - green;
				src.at<Vec3b>(row, col)[2] = 255 - red;
			}
			if (ch == 1) {
				int pv = src.at<uchar>(row, col);
				src.at<uchar>(row, col) = (255 - pv);
			}
		}
	}*/
	Mat result = Mat::zeros(src.size(), src.type());
	for (int row = 0; row < height; row++) {
		uchar* curr_row = src.ptr<uchar>(row);
		uchar* result_row = result.ptr<uchar>(row);
		for (int col = 0; col < width; col++) {
			if (dim == 3) {
				int blue = *curr_row++;
				int green = *curr_row++;
				int red = *curr_row++;

				*result_row++ = blue;
				*result_row++ = green;
				*result_row++ = red;
			}
			if (dim == 1) {
				int pv = *curr_row++;
				*result_row++ = pv;
			}
		}
	}
	imshow("pixel-demo", result);
	
	waitKey(0);
	destroyAllWindows();
	return 0;
}
