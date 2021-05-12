#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
int main(int arg, char** argv) {
	//默认的RGB3通道彩色图像加载，此外支持灰度图像与任意格式,IMREAD_UNCHANGED = -1 带透明通道，IMREAD_COLOR = 1 默认,IMREAD_GRAYSCALE=0 灰度图像
	Mat src = imread("D:/opencv/sources/samples/data/opencv-logo.png", IMREAD_UNCHANGED);
	if (src.empty()) {
		printf("图像为空");
		return -1;
	}
	namedWindow("001_demo", WINDOW_AUTOSIZE);//WINDOW_AUTOSIZE 自适应不可更改 ,WINDOW_FREERATIO 任意更改
	imshow("001_demo", src);//函数-图像显示，不支持透明通道
	imwrite("D://testopencv001.png", src);//保存图片，支持各种通道，本例因为src是带透明通道的，所以保存也是 
	waitKey(0);
	destroyAllWindows();
	return 0;
}