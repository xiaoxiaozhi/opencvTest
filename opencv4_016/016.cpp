#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
//图像的轮廓不仅能够提供物体的边缘，而且还能提供物体边缘之间的层次关系以及拓扑关系
//为了能够更好的表明各个轮廓之间的层级关系，常用4个参数来描述不同层级之间的结构关系
//同层下一个轮廓索引、同层上一个轮廓索引、下一层第一个子轮廓索引和上层父轮廓索引
RNG rng(12345);
void ccl_stats_demo(Mat &image);
void approxPoly();//轮廓逼近
//绘制轮廓函数
void drawapp(Mat result, Mat img2)
{
	for (int i = 0; i < result.rows; i++)
	{
		//最后一个坐标点与第一个坐标点连接
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

	// 二值化
	GaussianBlur(src, src, Size(3, 3), 0);
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

	//图像细化
	//thinning();

	// 轮廓发现 
	imshow("binary", binary);
	vector<vector<Point>> contours;
	vector<Vec4i> hirearchy;
	// hirearchy 轮廓结构
	//findContours(binary, contours, hirearchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());
	// 1. 单通道CV_8U 或者二值化图像 2. 检测到的轮库美格轮廓中存放着像素的坐标 3. 轮廓检测模式标志 4. 轮廓逼近方法标志 5.感兴趣区域提取轮廓 
	findContours(binary, contours, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());
	for (size_t t = 0; t < contours.size(); t++) {
		//3.如果是负数绘制所有轮廓  5. 线条粗细 6 线形 
		drawContours(src, contours, t, Scalar(0, 0, 255), 2, 8);
		//计算轮廓面积 2. 区域面积是否具有方向标志，true具有，默认false
		double area = contourArea(contours[t], false);
		//获取轮廓长度 1.轮廓曲线的2D像素 2. 是否闭合 
		double lenght = arcLength(contours[t], true);
		//通过面积和周长比值确定矩形
		cout << "面积 " << area << " 长度 " << lenght << endl;
	}
	//drawContours(src, contours, -1, Scalar(0, 0, 255), 2, 8);
	/*for (int i = 0; i < hirearchy.size(); i++)
	{
	cout << hirearchy[i] << endl;//打印轮廓向量的层级结构
	}*/
	//轮廓逼近 外界最大矩形，外接最小矩形，外接多边形
	//绘制多边形

	imshow("find contours demo", src);
}
void approxPoly() {
	Mat img = imread("D:/images/stuff.jpg");
	if (img.empty())
	{
		cout << "请确认图像文件名称是否正确" << endl;

	}

	Mat img1, img2;
	img.copyTo(img1);
	img.copyTo(img2);

	// 边缘检测
	Mat canny;
	Canny(img, canny, 80, 160, 3, false);
	imshow("canny", canny);
	//膨胀运算
	Mat kernel = getStructuringElement(0, Size(3, 3));
	dilate(canny, canny, kernel);

	// 轮廓发现与绘制
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(canny, contours, hierarchy, 0, 2, Point());


	for (size_t t = 0; t < contours.size(); t++)
	{
		//最大外接矩形逼近
		Rect rect = boundingRect(contours[t]);
		rectangle(img1, rect, Scalar(0, 0, 255), 2, 8, 0);

		//用最小外接矩形求取轮廓中心
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

		//2.中心点。3.半径 4.颜色 5.线条粗细程度，如果是负数则填充。6.线条类型，默认是8。 9.圆心坐标点和半径值的小数点位数
		//circle(img, center, 2, Scalar(0, 255, 0), 2, 8, 0);
		Mat result;
		//2.多边形逼近结果，以多边形顶点坐标的形式给出，3.逼近的精度，即原始曲线和逼近曲线之间的最大距离，4.逼近曲线是否为封闭曲线的标志，true 封闭
		approxPolyDP(contours[t], result, 4, true);  //多边形拟合
		drawapp(result, img);
		cout << "corners : " << result.rows << endl;

		//判断形状和绘制轮廓
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
