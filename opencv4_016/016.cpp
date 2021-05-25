#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
//ͼ������������ܹ��ṩ����ı�Ե�����һ����ṩ�����Ե֮��Ĳ�ι�ϵ�Լ����˹�ϵ
//Ϊ���ܹ����õı�����������֮��Ĳ㼶��ϵ������4��������������ͬ�㼶֮��Ľṹ��ϵ
//ͬ����һ������������ͬ����һ��������������һ���һ���������������ϲ㸸��������
RNG rng(12345);
void ccl_stats_demo(Mat &image);
void approxPoly();//�����ƽ�
//������������
void drawapp(Mat result, Mat img2)
{
	for (int i = 0; i < result.rows; i++)
	{
		//���һ����������һ�����������
		if (i == result.rows - 1)
		{
			Vec2i point1 = result.at<Vec2i>(i);
			Vec2i point2 = result.at<Vec2i>(0);
			line(img2, point1, point2, Scalar(0, 0, 255), 2, 8, 0);
			break;
		}
		Vec2i point1 = result.at<Vec2i>(i);
		Vec2i point2 = result.at<Vec2i>(i + 1);
		line(img2, point1, point2, Scalar(0, 0, 255), 2, 8, 0);
	}
}
void myContours();
int main(int argc, char** argv) {

	approxPoly();
	waitKey(0);
	destroyAllWindows();
	return 0;
}
void myContours() {
	Mat src = imread("D:/images/stuff.jpg");
	if (src.empty()) {
		printf("could not find image file");
		return;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	// ��ֵ��
	GaussianBlur(src, src, Size(3, 3), 0);
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

	//ͼ��ϸ��
	//thinning();

	// �������� 
	imshow("binary", binary);
	vector<vector<Point>> contours;
	vector<Vec4i> hirearchy;
	// hirearchy �����ṹ
	//findContours(binary, contours, hirearchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());
	// 1. ��ͨ��CV_8U ���߶�ֵ��ͼ�� 2. ��⵽���ֿ����������д�������ص����� 3. �������ģʽ��־ 4. �����ƽ�������־ 5.����Ȥ������ȡ���� 
	findContours(binary, contours, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());
	for (size_t t = 0; t < contours.size(); t++) {
		//3.����Ǹ���������������  5. ������ϸ 6 ���� 
		drawContours(src, contours, t, Scalar(0, 0, 255), 2, 8);
		//����������� 2. ��������Ƿ���з����־��true���У�Ĭ��false
		double area = contourArea(contours[t], false);
		//��ȡ�������� 1.�������ߵ�2D���� 2. �Ƿ�պ� 
		double lenght = arcLength(contours[t], true);
		//ͨ��������ܳ���ֵȷ������
		cout << "��� " << area << " ���� " << lenght << endl;
	}
	//drawContours(src, contours, -1, Scalar(0, 0, 255), 2, 8);
	/*for (int i = 0; i < hirearchy.size(); i++)
	{
	cout << hirearchy[i] << endl;//��ӡ���������Ĳ㼶�ṹ
	}*/
	//�����ƽ� ��������Σ������С���Σ���Ӷ����
	//���ƶ����

	imshow("find contours demo", src);
}
void approxPoly() {
	Mat img = imread("D:/images/stuff.jpg");
	if (img.empty())
	{
		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;

	}

	Mat img1, img2;
	img.copyTo(img1);
	img.copyTo(img2);

	// ��Ե���
	Mat canny;
	Canny(img, canny, 80, 160, 3, false);
	imshow("canny", canny);
	//��������
	Mat kernel = getStructuringElement(0, Size(3, 3));
	dilate(canny, canny, kernel);

	// �������������
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(canny, contours, hierarchy, 0, 2, Point());


	for (size_t t = 0; t < contours.size(); t++)
	{
		//�����Ӿ��αƽ�
		Rect rect = boundingRect(contours[t]);
		rectangle(img1, rect, Scalar(0, 0, 255), 2, 8, 0);

		//����С��Ӿ�����ȡ��������
		RotatedRect rrect = minAreaRect(contours[t]);
		Point2f points[4];
		rrect.points(points);
		Point2f center = rrect.center;
		for (size_t i = 0; i < 4; i++)
		{
			if (i == 3) {
				line(img2, points[i], points[0], Scalar(0, 255, 0), 2, 8, 0);
				break;
			}
			line(img2, points[i], points[i+1], Scalar(0, 255, 0), 2, 8, 0);
		}

		//2.���ĵ㡣3.�뾶 4.��ɫ 5.������ϸ�̶ȣ�����Ǹ�������䡣6.�������ͣ�Ĭ����8�� 9.Բ�������Ͱ뾶ֵ��С����λ��
		//circle(img, center, 2, Scalar(0, 255, 0), 2, 8, 0);
		Mat result;
		//2.����αƽ�������Զ���ζ����������ʽ������3.�ƽ��ľ��ȣ���ԭʼ���ߺͱƽ�����֮��������룬4.�ƽ������Ƿ�Ϊ������ߵı�־��true ���
		approxPolyDP(contours[t], result, 4, true);  //��������
		drawapp(result, img);
		cout << "corners : " << result.rows << endl;

		//�ж���״�ͻ�������
		if (result.rows == 3)
		{
		    putText(img, "triangle", center, 0, 1, Scalar(0, 255, 0), 1, 8);
		}
		if (result.rows == 4)
		{
			putText(img, "rectangle", center, 0, 1, Scalar(0, 255, 0), 1, 8);
		}
		if (result.rows == 8)
		{
			putText(img, "poly-8", center, 0, 1, Scalar(0, 255, 0), 1, 8);
		}
		if (result.rows > 12)
		{
			putText(img, "circle", center, 0, 1, Scalar(0, 255, 0), 1, 8);
		}
	}
	imshow("boundingRect", img1);
	imshow("minAreaRect", img2);
	imshow("approxPolyDP", img);
}
