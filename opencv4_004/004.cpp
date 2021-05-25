#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
int main(int arg, char** argv) {
	//mat.at<type> 对应
	//https://blog.csdn.net/qq_28584889/article/details/102958731?utm_medium=distribute.pc_relevant.none-task-blog-baidujs_title-1&spm=1001.2101.3001.4242 
	Mat src = imread("D:/images/car.jpg");//默认的RGB彩色图像加载，此外支持灰度图像与任意格式
	if (src.empty()) {
		printf("图像为空");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);//
	Mat b;
	Mat temp = Mat::zeros(src.size(), CV_8UC1);
	temp = Scalar(255);

	for (int i = 0; i < src.rows/10; i++)
	{
		for (int j = 0; j < src.cols/10; j++)
		{
			cout<<"单通道原始值"<<src.at<Vec3b>(i, j)[0]<<endl;
		}
	}
	//取反操作 temp 的每个像素值1 的时候 bitwise_not 按位取反， 0的时候不执行。理解有误差待议
	bitwise_not(src, b, temp);
	imshow("bitsiwse_not", b);//按位取反 ，相当于255 - 原像素

	// 显示图像一部分  
	/*Mat mask = Mat::zeros(src.size(), CV_8UC1);
	int h = mask.rows/ 4 *3;
	int w = mask.cols / 4 *3;
	for (int row = 100; row < h;row++) {
		for (int col = 100; col < w;col++) {
			mask.at<uchar>(row,col) = 255;
		}
	}
	Mat b1;
	bitwise_not(src, b1, mask);
	imshow("bitsiwse_not_sub", b1);
	//与操作  取到原图 
	Mat b2;
	bitwise_and(src,src, b2, mask);
	imshow("bitsiwse_and", b2);*/
	
	// 或操作 


	waitKey(0);
	destroyAllWindows();
	return 0;
}