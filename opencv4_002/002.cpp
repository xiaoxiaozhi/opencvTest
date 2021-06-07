#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
int main(int arg, char** argv) {
	//-----------------------------创建Mat类-----------------------------------------------------
	//mat类包数据格式  矩阵头+数据  矩阵头：尺寸 行数 列数 数据类型 通道数 引用次数
	//opencv 为了屏蔽硬件 操作系统差异，数据类型进行强制对应 数据类型对应位数详见 mat数据格式.jpg。 
	//mat.at<type> 对应
	//https://blog.csdn.net/qq_28584889/article/details/102958731?utm_medium=distribute.pc_relevant.none-task-blog-baidujs_title-1&spm=1001.2101.3001.4242 
	//认识 Mat 
	Mat a(3, 3, CV_8U);// 创建一个Mat类方式一    宽高数据类型，数据类型默认是单通道
	Mat b(1, 3, CV_8UC1, Scalar(20));//
	Mat c(3, 3, CV_8UC2);//双通道
	Mat d(3, 3, CV_8UC3, Scalar(10, 100, 255));//三通道

	Mat e(Size(10, 10), CV_8UC1);//创建一个Mat类方式二  Size(行,列)

	Mat f(e, Range(2, 5), Range(2, 5)); //创建一个Mat类 方式三 在原有Mat类基础上截取一部分 第一个Range是行，第二个Range是列。本例Range： 5>取值≥2  Range从0开始

	Mat g(10, 10, CV_8UC1, Scalar(255));//创建一个Mat类 方式四 在定义过程中赋值 Scalar()总共有5个参数

	Mat h = Mat::eye(4, 4, CV_8U);// 创建一个Mat类 方式五 Mat默认提供了4种方式，eye单位矩阵 diag对角矩阵 ones元素全为1的矩阵 zeros元素全为0的矩阵

	Mat i = (Mat_<int>(1, 3) << 1, 2, 3);// 创建一个Mat类 方式六 枚举法 。直接通过输入流的形式
	cout << "枚举法赋值\n" << i << endl;
	Mat diag1 = Mat::diag(i);// 对角矩阵 要求输入 是一个 1*n 的矩阵 .一维的矩阵 变成对角线
	cout << "对角矩阵\n" << diag1 << endl;

	Mat m4 = i.clone();//克隆已有的图像 方式一
	i.copyTo(m4);//克隆已有的图像 方式二


	//----------------------------Mat类读取------------------------------------
	Mat src = Mat(5, 5, CV_8UC3, Scalar(0, 100, 254));
	int width = src.cols;//像素宽度
	int height = src.rows;//像素高度
	int elemByte = src.elemSize(); //每个像素的字节数 通道数*数据类型
	int total = src.total();// 像素个数
	int step = src.step;//矩阵宽度,相当于像素列*通道数
	int dim = src.channels();//通道数
	cout << "src 矩阵\n" << src << endl;
	cout << "total" << total << "\telemByte" << elemByte << "\tstep" << src.step << "\t cols" << src.cols << endl;
	cout << "单通道矩阵元素读取\t" << (int)a.at<uchar>(2, 2) << endl;//单通道矩阵元素读取，只有单通道才能使用此方法
	cout << "多通道矩阵元素读取\t" << src.at<Vec3b>(0, 0)[1] << endl;// Vec2b 对应双通道 Vec4b 对应4通道
	int num = (int)(*(src.data + src.step[0] * 1 + b.step[1] * 1 + dim));//矩阵元素地址定位方式访问元素，不用考虑数据类型，src.step[0] * x 代表x   b.step[1] * y代表y  
	cout << "地址定位" << num << endl;

	//--------------------------Mat类运算----------------------------------------


	waitKey(0);
	destroyAllWindows();
	return -1;
}