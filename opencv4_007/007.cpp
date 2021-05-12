#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
int main(int arg, char** argv) {
	Mat canvas = imread("D://images/face.jpg");
	vector<Mat> mm;
	//ͨ������
	split(canvas, mm);
	namedWindow("canvas", WINDOW_AUTOSIZE);
	printf("�����%d��ͨ��",mm.size());
	imshow("blue",mm[0]);
	imshow("green", mm[1]);
	imshow("red", mm[2]);//���ֺ�ɫͨ������������


	//ͨ���ϲ�
	mm[2] = Scalar(0);
	Mat dst;
	merge(mm, dst);
	imshow("�ϲ�", dst);

	//��ͼ
	Rect rect;
	rect.x = 50;
	rect.y = 50;
	rect.width = 100;
	rect.height = 100;
	Mat sub = canvas(rect);
	imshow("SUB", sub);
	waitKey(0);
	destroyAllWindows();
	return 0;
}