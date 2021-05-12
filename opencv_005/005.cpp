#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
int main(int arg, char** argv) {
	Mat src = imread("D://images/apple.jpg",IMREAD_GRAYSCALE);//默认的RGB彩色图像加载，此外支持灰度图像与任意格式
	if (src.empty()) {
		printf("图像为空");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);//函数-图像显示，不支持透明通道

	//最大值最小值  只能计算单通道
	double minVal,maxVal;
	Point maxPoint, minPoint;
	minMaxLoc(src,&minVal,&maxVal,&minPoint,&maxPoint);
	printf("minVal = %0.2f maxVal = %0.2f \n",minVal,maxVal);
	printf("minPoint.x = %d minPoint.y = %d \n", minPoint.x, minPoint.y);//最小值所在点

	//均值 单通道     
	Scalar s = mean(src);//均值
	printf("均值 mean = %0.2f\n",s[0]);//s[1] s[2] 其它两个通道
	Mat mm,std;
	//均值、方差 计算多通道
	Mat src1 = imread("D://images/apple.jpg");//默认的RGB彩色图像加载，此外支持灰度图像与任意格式
	meanStdDev(src1, mm, std);

	printf("mm.rows = %d", mm.rows);
	printf("\t多通道均值 %0.2f %0.2f %0.2f\n",mm.at<double>(0,0), mm.at<double>(1, 0), mm.at<double>(2, 0));//mm.at<double> 得到一个Scale类型

	printf("std.rows = %d\t", std.rows);//应用实例，如果方差特别小，可以判定为图像变化不到这种情况可以过滤掉，例如(0,0,0)
	printf("多通道方差 %0.2f %0.2f %0.2f\n", std.at<double>(0, 0), std.at<double>(1, 0), std.at<double>(2, 0));

	waitKey(0);
	destroyAllWindows();
	return 0;
}