#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
int main(int arg, char** argv) {
	Mat src = imread("D://images/22.jpg");//默认的RGB彩色图像加载，此外支持灰度图像与任意格式
	if (src.empty()) {
		printf("图像为空");
		return - 1;
	}
	
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);//函数-图像显示，不支持透明通道
	Mat labels = Mat::zeros(src.size(), CV_32S);
	imshow("input", labels);//函数-图像显示，不支持透明通道
	waitKey(0);
	destroyAllWindows();
	return 0;
}