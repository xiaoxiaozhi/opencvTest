#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
/*
��������
*/
int main(int arg, char** argv) {
	Mat src1 = imread("D:/images/LinuxLogo.jpg", IMREAD_COLOR);
	Mat src2 = imread("D:/images/WindowsLogo.jpg", IMREAD_COLOR);
	if (src1.empty() || src2.empty()) {
		printf("ͼ��Ϊ��");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("src1", src1);//����-ͼ����ʾ����֧��͸��ͨ��
	imshow("src2", src2);//����-ͼ����ʾ����֧��͸��ͨ��

	/*Mat dst1;
	add(src1, src2, dst1);
	imshow("add",dst1);

	Mat dst2;
	subtract(src1, src2, dst2);
	imshow("subtract", dst2);

	Mat dst3;
	multiply(src1, src2, dst3);
	imshow("multiply", dst3);

	Mat dst4;
	divide(src1, src2, dst4);
	imshow("divide", dst4);*/

	//ͨ���Ӽ��������� ,BGR ֵԽ��Խ��
	Mat src3 = imread("D:/images/orange.jpg", IMREAD_COLOR);
	Mat black = Mat::zeros(src3.size(), src3.type());
	black = Scalar(40,40,40);
	Mat mat5;
	
	imshow("src3", src3);
	add(src3, black, mat5);
	imshow("add", mat5);
	subtract(src3, black, mat5);
	imshow("subtract", mat5);
	
	//�Աȶ�
	Mat dst2;
	//2 ÿ�����س���2 �����Աȶȣ� temp�ı�����,0.5ֻ����һ������� 0.0gama ���岻��
	//Mat temp1 = Mat::zeros(src1.size(), src1.type());
	addWeighted(src3,1.2, black,0.5,0.0,dst2);
	imshow("dst2", dst2);

	waitKey(0);
	destroyAllWindows();
	return 0;
}