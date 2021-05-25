#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
int main(int arg, char** argv) {
	//Ĭ�ϵ�RGB3ͨ����ɫͼ����أ�����֧�ֻҶ�ͼ���������ʽ,IMREAD_UNCHANGED = -1 ��͸��ͨ����IMREAD_COLOR = 1 Ĭ��,IMREAD_GRAYSCALE=0 �Ҷ�ͼ��
	Mat src = imread("D:/images/lena.jpg", IMREAD_COLOR);
	if (src.empty()) {
		printf("ͼ��Ϊ��");
		return -1;
	}
	namedWindow("002_demo", WINDOW_AUTOSIZE);//WINDOW_AUTOSIZE ����Ӧ���ɸ��� ,WINDOW_FREERATIO �������
	imshow("002_demo", src);//����-ͼ����ʾ����֧��͸��ͨ��
	imwrite("D://testopencv001.png", src);//����ͼƬ��֧�ָ���ͨ����������Ϊsrc�Ǵ�͸��ͨ���ģ����Ա���Ҳ�� 

	//��ʶ Mat 
	int width = src.cols;
	int height = src.rows;
	int dim = src.channels();//ͨ����
	int d = src.depth();//
	int t = src.type();//ͼ�����ͣ���ʾ��ͨ��
	if (d == CV_8U) {
		printf("d = %s ", "CV_8U");
	}
	if (t == CV_8UC3) {
		printf("t = %s ", "CV_8UC3");
	}
	printf("width = %d height = %d dim = %d d = %d t = %d", width, height, dim, d, t);


	//������ͨ��Mat
	Mat mat1 = Mat(256, 256, CV_8UC1);//��С 256����ͨ������ͨ��Ĭ���ǻҶ�ͼ��
	mat1 = Scalar(66);//���� ��ɫֵ
	imshow("t1", mat1);

	//������ͨ��Mat
	Mat mat2 = Mat(Size(256, 256), CV_8UC3);//��С 256����ͨ������ͨ��Ĭ���ǻҶ�ͼ��
	mat2 = Scalar(66, 55, 44);//���� ��ɫֵ
	imshow("t2", mat2);

	//������ͨ������0��ͼ��
	Mat mat3 = Mat::zeros(Size(256, 256), CV_8UC3);//��С 256����ͨ������ͨ��Ĭ���ǻҶ�ͼ��
	imshow("t3", mat3);

	//��¡���е�ͼ�� ��ʽһ
	Mat m4 = mat3.clone();
	//��¡���е�ͼ�� ��ʽ��
	mat3.copyTo(m4);

	// ������ԭͼ��С ͨ��һ����ͼƬ
	Mat mat5 = Mat::zeros(src.size(),src.type());
	//����ÿһ������
	for (int col = 0; col < width;col++) { //Mat���е�at�������ã����ڻ�ȡͼ�����ĳ���ֵ��ı�ĳ���ֵ�� 
		for (int row = 0; row < height; row++){
			if (dim == 3) {
				Vec3b pix = src.at<Vec3b>(col, row);//Vec3b 3ͨ��rgb
				int blue = pix[0];
				int green = pix[1];
				int red = pix[3];
				src.at<Vec3b>(col, row)[0] = 255 - blue;
				src.at<Vec3b>(col, row)[1] = 255 - green;
				src.at<Vec3b>(col, row)[2] = 255 - red;
			}
			if (dim == 1) {//��ͨ��
				int pv = src.at<uchar>(col,row);
				src.at<uchar>(col, row) = 255 - pv;
			}
		}
	}
	Mat mat6 = Mat::zeros(src.size(), src.type());
	for (int row = 0; row < height; row++) {
		uchar* curr_r = src.ptr<uchar>(row);
		uchar* mat6_r = mat6.ptr<uchar>(row);
		for (int col = 0; col < width; col++) {
			if (dim == 3) {
				//printf("�޸�����ֵ");
				int blue = *curr_r++;
				int green = *curr_r++;
				int red = *curr_r++;
				*mat6_r++ = 255 - blue;
				*mat6_r++ = 255 - green;
				*mat6_r++ = 255 - red;
			}
			if (dim == 1) {//��ͨ��
				int pv = *curr_r++;
				*mat6_r = 255 - pv;
			}
		}
		
	}
		imshow("t4", mat6);

		waitKey(0);
		destroyAllWindows();
		return 0;
	}