#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	//【1】读取原图并显示
	Mat srcImage = imread("D://images/flower.png", 0);
	imshow("原图：", srcImage);
	if (!srcImage.data) {
		cout << "fail to load image" << endl;
		return 0;
	}
}