#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
int main(int arg, char** argv) {
	Mat src = imread("D://images/22.jpg");//Ĭ�ϵ�RGB��ɫͼ����أ�����֧�ֻҶ�ͼ���������ʽ
	if (src.empty()) {
		printf("ͼ��Ϊ��");
		return - 1;
	}
	
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);//����-ͼ����ʾ����֧��͸��ͨ��
	Mat labels = Mat::zeros(src.size(), CV_32S);
	imshow("input", labels);//����-ͼ����ʾ����֧��͸��ͨ��
	waitKey(0);
	destroyAllWindows();
	return 0;
}