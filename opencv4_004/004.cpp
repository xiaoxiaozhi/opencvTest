#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
int main(int arg, char** argv) {
	Mat src = imread("D:/images/orange.jpg");//Ĭ�ϵ�RGB��ɫͼ����أ�����֧�ֻҶ�ͼ���������ʽ
	if (src.empty()) {
		printf("ͼ��Ϊ��");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);//
	Mat b;
	Mat temp = Mat::zeros(src.size(), CV_8UC1);
	temp = Scalar(255);
	//ȡ������ temp ��ÿ������ֵ1 ��ʱ�� bitwise_not ��λȡ���� 0��ʱ��ִ�С������������
	bitwise_not(src, b, temp);
	imshow("bitsiwse_not", b);//��λȡ�� ���൱��255 - ԭ����

	// ��ʾͼ��һ����  
	Mat mask = Mat::zeros(src.size(), CV_8UC1);
	int h = mask.rows/ 4 *3;
	int w = mask.cols / 4 *3;
	for (int row = 100; row < h;row++) {
		for (int col = 100; col < w;col++) {
			mask.at<uchar>(row,col) = 255;
		}
	}
	/*Mat b1;
	bitwise_not(src, b1, mask);
	imshow("bitsiwse_not_sub", b1);*/
	//�����  ȡ��ԭͼ 
	Mat b2;
	bitwise_and(src,src, b2, mask);
	imshow("bitsiwse_and", b2);
	
	// ����� 


	waitKey(0);
	destroyAllWindows();
	return 0;
}