#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
void hough_linesp_demo();
int main(int argc, char** argv) {
	// hough_linesp_demo();
	
	Mat src = imread("D:/images/tline.png");
	if (src.empty()) {
		printf("could not find image file");
		return -1;
	}

	// ��ֵ��
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	namedWindow("binary", WINDOW_AUTOSIZE);
	imshow("binary", binary);

	// ����ֱ�߼��
	vector<Vec3f> lines;
	HoughLines(binary, lines, 1, CV_PI / 180.0, 100, 0, 0);
	
	// ����ֱ��
	Point pt1, pt2;
	for (size_t i = 0; i < lines.size(); i++) {
		float rho = lines[i][0]; // ����
		float theta = lines[i][1]; // �Ƕ�
		float acc = lines[i][2];// �ۼ�ֵ
		printf("rho: %.2f, theta : %.2f, acc: %.2f \n", rho, theta, acc);
		double a = cos(theta);
		double b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		int angle = round((theta / CV_PI) * 180);
		printf("angle : %d \n", angle);
		if (rho > 0) { // ����
			line(src, pt1, pt2, Scalar(0, 0, 255), 1, 8, 0);
			if (angle == 90) { // ˮƽ��
				line(src, pt1, pt2, Scalar(0, 255, 255), 2, 8, 0);
			}
			if (angle <= 1) {// ��ֱ��
				line(src, pt1, pt2, Scalar(255, 255, 0), 4, 8, 0);
			}
		}
		else { // ����
			line(src, pt1, pt2, Scalar(255, 0, 0), 2, 8, 0);
		}
	}
	imshow("hough line detection", src);
	
	waitKey(0);
	destroyAllWindows();
	return 0;
}

void hough_linesp_demo() {
	Mat src = imread("D:/images/morph01.png");
	Mat binary;
	Canny(src, binary, 80, 160, 3, false);
	imshow("binary", binary);

	vector<Vec4i> lines;
	HoughLinesP(binary, lines, 1, CV_PI / 180, 80, 200, 10);
	Mat result = Mat::zeros(src.size(), src.type());
	for (int i = 0; i < lines.size(); i++) {
		line(result, Point(lines[i][0], lines[i][1]), Point(lines[i][2], lines[i][3]), Scalar(0, 0, 255), 1, 8);
	}
	imshow("hough linesp demo", result);
}
