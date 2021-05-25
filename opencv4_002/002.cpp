#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
int main(int arg, char** argv) {
	//默认的RGB3通道彩色图像加载，此外支持灰度图像与任意格式,IMREAD_UNCHANGED = -1 带透明通道，IMREAD_COLOR = 1 默认,IMREAD_GRAYSCALE=0 灰度图像
	Mat src = imread("D:/images/lena.jpg", IMREAD_COLOR);
	if (src.empty()) {
		printf("图像为空");
		return -1;
	}
	namedWindow("002_demo", WINDOW_AUTOSIZE);//WINDOW_AUTOSIZE 自适应不可更改 ,WINDOW_FREERATIO 任意更改
	imshow("002_demo", src);//函数-图像显示，不支持透明通道
	imwrite("D://testopencv001.png", src);//保存图片，支持各种通道，本例因为src是带透明通道的，所以保存也是 

	//认识 Mat 
	int width = src.cols;
	int height = src.rows;
	int dim = src.channels();//通道数
	int d = src.depth();//
	int t = src.type();//图像类型，表示几通道
	if (d == CV_8U) {
		printf("d = %s ", "CV_8U");
	}
	if (t == CV_8UC3) {
		printf("t = %s ", "CV_8UC3");
	}
	printf("width = %d height = %d dim = %d d = %d t = %d", width, height, dim, d, t);


	//创建单通道Mat
	Mat mat1 = Mat(256, 256, CV_8UC1);//大小 256，单通道，单通道默认是灰度图像
	mat1 = Scalar(66);//标量 颜色值
	imshow("t1", mat1);

	//创建三通道Mat
	Mat mat2 = Mat(Size(256, 256), CV_8UC3);//大小 256，单通道，单通道默认是灰度图像
	mat2 = Scalar(66, 55, 44);//标量 颜色值
	imshow("t2", mat2);

	//创建三通道都是0的图像
	Mat mat3 = Mat::zeros(Size(256, 256), CV_8UC3);//大小 256，单通道，单通道默认是灰度图像
	imshow("t3", mat3);

	//克隆已有的图像 方式一
	Mat m4 = mat3.clone();
	//克隆已有的图像 方式二
	mat3.copyTo(m4);

	// 创建跟原图大小 通道一样的图片
	Mat mat5 = Mat::zeros(src.size(),src.type());
	//遍历每一个像素
	for (int col = 0; col < width;col++) { //Mat类中的at方法作用：用于获取图像矩阵某点的值或改变某点的值。 
		for (int row = 0; row < height; row++){
			if (dim == 3) {
				Vec3b pix = src.at<Vec3b>(col, row);//Vec3b 3通道rgb
				int blue = pix[0];
				int green = pix[1];
				int red = pix[3];
				src.at<Vec3b>(col, row)[0] = 255 - blue;
				src.at<Vec3b>(col, row)[1] = 255 - green;
				src.at<Vec3b>(col, row)[2] = 255 - red;
			}
			if (dim == 1) {//单通道
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
				//printf("修改像素值");
				int blue = *curr_r++;
				int green = *curr_r++;
				int red = *curr_r++;
				*mat6_r++ = 255 - blue;
				*mat6_r++ = 255 - green;
				*mat6_r++ = 255 - red;
			}
			if (dim == 1) {//单通道
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