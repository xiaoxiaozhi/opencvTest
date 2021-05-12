#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
	namedWindow("canvas", WINDOW_AUTOSIZE);
	
	// 相关绘制API演示
	line(canvas, Point(10, 10), Point(400, 400), Scalar(0, 0, 255), 1, LINE_8);
	Rect rect(100, 100, 200, 200);
	rectangle(canvas, rect, Scalar(255, 0, 0), 1, 8);
	circle(canvas, Point(256, 256), 100, Scalar(0, 255, 0), -1, 8);
	putText(canvas, "hello, opencv", Point(100, 50), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0, 255, 0), 2, 8);
	RotatedRect rrt;
	rrt.center = Point2f(256, 256);
	rrt.angle = 45.0;
	rrt.size = Size(100, 200);
	ellipse(canvas, rrt, Scalar(0, 255, 255), -1, 8);
	imshow("canvas", canvas);

	Mat image = Mat::zeros(Size(512, 512), CV_8UC3);
	int x1 = 0, y1 = 0;
	int x2 = 0, y2 = 0;
	RNG rng(12345);
	while (true) {
		x1 = (int)rng.uniform(0, 512);
		x2 = (int)rng.uniform(0, 512);
		y1 = (int)rng.uniform(0, 512);
		y2 = (int)rng.uniform(0, 512);
		int w = abs(x2 - x1);
		int h = abs(y2 - y1);
		rect.x = x1;
		rect.y = y1;
		rect.width = w;
		rect.height = h;
		// image = Scalar(0, 0, 0);
		rectangle(image, rect, Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256)), 1, 8);
		// line(image, Point(x1, y1), Point(x2, y2), Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256)), 1, LINE_8);
		imshow("image", image);
		char c = waitKey(10);
		if (c == 27) {
			break;
		}
	}

	waitKey(0);
	destroyAllWindows();
	return 0;
}
