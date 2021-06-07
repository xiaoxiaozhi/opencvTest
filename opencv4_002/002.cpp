#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
int main(int arg, char** argv) {
	//-----------------------------����Mat��-----------------------------------------------------
	//mat������ݸ�ʽ  ����ͷ+����  ����ͷ���ߴ� ���� ���� �������� ͨ���� ���ô���
	//opencv Ϊ������Ӳ�� ����ϵͳ���죬�������ͽ���ǿ�ƶ�Ӧ �������Ͷ�Ӧλ����� mat���ݸ�ʽ.jpg�� 
	//mat.at<type> ��Ӧ
	//https://blog.csdn.net/qq_28584889/article/details/102958731?utm_medium=distribute.pc_relevant.none-task-blog-baidujs_title-1&spm=1001.2101.3001.4242 
	//��ʶ Mat 
	Mat a(3, 3, CV_8U);// ����һ��Mat�෽ʽһ    ����������ͣ���������Ĭ���ǵ�ͨ��
	Mat b(1, 3, CV_8UC1, Scalar(20));//
	Mat c(3, 3, CV_8UC2);//˫ͨ��
	Mat d(3, 3, CV_8UC3, Scalar(10, 100, 255));//��ͨ��

	Mat e(Size(10, 10), CV_8UC1);//����һ��Mat�෽ʽ��  Size(��,��)

	Mat f(e, Range(2, 5), Range(2, 5)); //����һ��Mat�� ��ʽ�� ��ԭ��Mat������Ͻ�ȡһ���� ��һ��Range���У��ڶ���Range���С�����Range�� 5>ȡֵ��2  Range��0��ʼ

	Mat g(10, 10, CV_8UC1, Scalar(255));//����һ��Mat�� ��ʽ�� �ڶ�������и�ֵ Scalar()�ܹ���5������

	Mat h = Mat::eye(4, 4, CV_8U);// ����һ��Mat�� ��ʽ�� MatĬ���ṩ��4�ַ�ʽ��eye��λ���� diag�ԽǾ��� onesԪ��ȫΪ1�ľ��� zerosԪ��ȫΪ0�ľ���

	Mat i = (Mat_<int>(1, 3) << 1, 2, 3);// ����һ��Mat�� ��ʽ�� ö�ٷ� ��ֱ��ͨ������������ʽ
	cout << "ö�ٷ���ֵ\n" << i << endl;
	Mat diag1 = Mat::diag(i);// �ԽǾ��� Ҫ������ ��һ�� 1*n �ľ��� .һά�ľ��� ��ɶԽ���
	cout << "�ԽǾ���\n" << diag1 << endl;

	Mat m4 = i.clone();//��¡���е�ͼ�� ��ʽһ
	i.copyTo(m4);//��¡���е�ͼ�� ��ʽ��


	//----------------------------Mat���ȡ------------------------------------
	Mat src = Mat(5, 5, CV_8UC3, Scalar(0, 100, 254));
	int width = src.cols;//���ؿ��
	int height = src.rows;//���ظ߶�
	int elemByte = src.elemSize(); //ÿ�����ص��ֽ��� ͨ����*��������
	int total = src.total();// ���ظ���
	int step = src.step;//������,�൱��������*ͨ����
	int dim = src.channels();//ͨ����
	cout << "src ����\n" << src << endl;
	cout << "total" << total << "\telemByte" << elemByte << "\tstep" << src.step << "\t cols" << src.cols << endl;
	cout << "��ͨ������Ԫ�ض�ȡ\t" << (int)a.at<uchar>(2, 2) << endl;//��ͨ������Ԫ�ض�ȡ��ֻ�е�ͨ������ʹ�ô˷���
	cout << "��ͨ������Ԫ�ض�ȡ\t" << src.at<Vec3b>(0, 0)[1] << endl;// Vec2b ��Ӧ˫ͨ�� Vec4b ��Ӧ4ͨ��
	int num = (int)(*(src.data + src.step[0] * 1 + b.step[1] * 1 + dim));//����Ԫ�ص�ַ��λ��ʽ����Ԫ�أ����ÿ����������ͣ�src.step[0] * x ����x   b.step[1] * y����y  
	cout << "��ַ��λ" << num << endl;

	//--------------------------Mat������----------------------------------------


	waitKey(0);
	destroyAllWindows();
	return -1;
}