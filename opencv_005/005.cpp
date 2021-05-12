#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
int main(int arg, char** argv) {
	Mat src = imread("D://images/apple.jpg",IMREAD_GRAYSCALE);//Ĭ�ϵ�RGB��ɫͼ����أ�����֧�ֻҶ�ͼ���������ʽ
	if (src.empty()) {
		printf("ͼ��Ϊ��");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);//����-ͼ����ʾ����֧��͸��ͨ��

	//���ֵ��Сֵ  ֻ�ܼ��㵥ͨ��
	double minVal,maxVal;
	Point maxPoint, minPoint;
	minMaxLoc(src,&minVal,&maxVal,&minPoint,&maxPoint);
	printf("minVal = %0.2f maxVal = %0.2f \n",minVal,maxVal);
	printf("minPoint.x = %d minPoint.y = %d \n", minPoint.x, minPoint.y);//��Сֵ���ڵ�

	//��ֵ ��ͨ��     
	Scalar s = mean(src);//��ֵ
	printf("��ֵ mean = %0.2f\n",s[0]);//s[1] s[2] ��������ͨ��
	Mat mm,std;
	//��ֵ������ �����ͨ��
	Mat src1 = imread("D://images/apple.jpg");//Ĭ�ϵ�RGB��ɫͼ����أ�����֧�ֻҶ�ͼ���������ʽ
	meanStdDev(src1, mm, std);

	printf("mm.rows = %d", mm.rows);
	printf("\t��ͨ����ֵ %0.2f %0.2f %0.2f\n",mm.at<double>(0,0), mm.at<double>(1, 0), mm.at<double>(2, 0));//mm.at<double> �õ�һ��Scale����

	printf("std.rows = %d\t", std.rows);//Ӧ��ʵ������������ر�С�������ж�Ϊͼ��仯��������������Թ��˵�������(0,0,0)
	printf("��ͨ������ %0.2f %0.2f %0.2f\n", std.at<double>(0, 0), std.at<double>(1, 0), std.at<double>(2, 0));

	waitKey(0);
	destroyAllWindows();
	return 0;
}