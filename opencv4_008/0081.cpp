#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	//��1����ȡԭͼ����ʾ
	Mat srcImage = imread("D://images/flower.png", 0);
	imshow("ԭͼ��", srcImage);
	if (!srcImage.data) {
		cout << "fail to load image" << endl;
		return 0;
	}
}