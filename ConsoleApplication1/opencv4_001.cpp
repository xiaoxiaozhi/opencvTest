#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
int main(int arg, char** argv) {
	//Ĭ�ϵ�RGB3ͨ����ɫͼ����أ�����֧�ֻҶ�ͼ���������ʽ,IMREAD_UNCHANGED = -1 ��͸��ͨ����IMREAD_COLOR = 1 Ĭ��,IMREAD_GRAYSCALE=0 �Ҷ�ͼ��
	Mat src = imread("D:/opencv/sources/samples/data/opencv-logo.png", IMREAD_UNCHANGED);
	if (src.empty()) {
		printf("ͼ��Ϊ��");
		return -1;
	}
	namedWindow("001_demo", WINDOW_AUTOSIZE);//WINDOW_AUTOSIZE ����Ӧ���ɸ��� ,WINDOW_FREERATIO �������
	imshow("001_demo", src);//����-ͼ����ʾ����֧��͸��ͨ��
	imwrite("D://testopencv001.png", src);//����ͼƬ��֧�ָ���ͨ����������Ϊsrc�Ǵ�͸��ͨ���ģ����Ա���Ҳ�� 
	waitKey(0);
	destroyAllWindows();
	return 0;
}