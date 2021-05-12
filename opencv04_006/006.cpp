#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
int main(int arg, char** argv) {
	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
	canvas = Scalar(255,255,255);
	namedWindow("canvas", WINDOW_AUTOSIZE);
	//绘制线段
	line(canvas, Point(100, 100), Point(200, 100), Scalar(0, 55, 66), 1, LINE_8);// 1 代表线宽 LINE_8 绘制方式
	imshow("canvas", canvas);//函数-图像显示，不支持透明通道

	//绘制文字
	putText(canvas, "hello", Point(100, 100), FONT_HERSHEY_SIMPLEX,2.0,Scalar(0, 255, 0), 2, LINE_8);//fontScale 传1.0 就显示不了文字，必须穿2.0  原因未知
	imshow("putText", canvas);

	//绘制矩形  线宽小于0变成填充
	Rect rect = Rect(100,100,200,200);
	canvas = Scalar(255, 255, 255);
	rectangle(canvas, rect, Scalar(0, 55, 66), 1, LINE_8);
	imshow("rect", canvas);

	//绘制原型 
	canvas = Scalar(255, 255, 255);
	circle(canvas, Point(200,200), 100,Scalar(0, 55, 66), 1, LINE_8);
	imshow("circle", canvas);

	//绘制椭圆
	RotatedRect rrt;
	rrt.center = Point(200, 200);
	rrt.angle = 90;//角度 0垂直 90水平
	rrt.size = Size(100,200);//椭圆的宽和高
	ellipse(canvas, rrt, Scalar(0, 55, 66), -1, LINE_8);
	imshow("ellipse", canvas);

	//使用随机数 RNG
	RNG mg(123456);
	canvas = Scalar(255, 255, 255);
	while (true)
	{
		int x1 = mg.uniform(0, 512);
		int y1 = mg.uniform(0, 512);
		int x2 = mg.uniform(0, 512);
		int y2 = mg.uniform(0, 512);
		line(canvas, Point(x1, y1), Point(x2, y2), Scalar(mg.uniform(0, 255),mg.uniform(0, 255), mg.uniform(0, 255)), 1, LINE_8);
		imshow("RNG",canvas);
		char c = waitKey(10);
		if (c ==27) {
			break;
		}
	}
	waitKey(0);
	destroyAllWindows();
	return 0;
}