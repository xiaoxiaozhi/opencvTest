#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
int otherHist();
//均衡的结果是图像对比度的增加。均衡能够使对比度较低的局部区域获得高对比度，从而分散最频繁的强度。当图像非常暗或者非常亮，并且背景和前景之间存在非常小的差异时，此方法非常有用。通过使用直方图均衡化，可以增加对比度，并提升暴露过度或暴露不足的细节。该技术在医学图像（例如X射线）中非常有用。
int main(int arg, char** argv) {
	Mat canvas = imread("D://images/flower.png",IMREAD_COLOR);
	if (canvas.empty()) {
		printf("图像为空");
		waitKey(0);
		destroyAllWindows();
		return -1;
	}
	vector<Mat> mm;
	//通道分离
	split(canvas, mm);
	namedWindow("canvas", WINDOW_AUTOSIZE);
	printf("分离出%d个通道", mm.size());
	//计算直方图
	int histSize = 256;
	Mat b_hist, g_hist, r_hist;
	float range[] = { 0,255 };
	const float* histranges{ range };
	calcHist(&mm[0], 1, 0, Mat(),b_hist, 1, &histSize, &histranges, true, false);
	calcHist(&mm[1], 1, 0, Mat(), g_hist, 1, &histSize, &histranges, true, false);
	calcHist(&mm[2], 1, 0, Mat(),r_hist, 1, &histSize, &histranges, true, false);
	
	Mat result = Mat::zeros(Size(600, 400), CV_8UC3);
	int margin = 50;
	int nm = result.rows - 2 * margin;
	//
	normalize(b_hist,b_hist,
		0,//均衡化最小值
		nm,//均衡化最大值
		NORM_MINMAX,//归一化所用的计算公式
		-1,Mat());
	normalize(g_hist,g_hist, 0, nm, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, nm, NORM_MINMAX, -1, Mat());
	
	float step = 500 / 256.0;
	for (int i = 0; i < 255; i++)
	{
		float bh1 = b_hist.at<float>(i, 0);
		float bh2 = b_hist.at<float>(i+1, 0);
		line(result, Point(step*i, 50 + (nm - bh1)), Point(step*(i + 1), 50 + (nm - bh2)), Scalar(255, 0, 0), 2, 8, 0);

		float gh1 = g_hist.at<float>(i, 0);
		float gh2 = g_hist.at<float>(i + 1, 0);
		line(result, Point(step*i, 50 + (nm - gh1)), Point(step*(i + 1), 50 + (nm - gh2)), Scalar(0, 255, 0),2,8,0);

		float rh1 = r_hist.at<float>(i, 0);
		float rh2 = r_hist.at<float>(i + 1, 0);
		line(result, Point(step*i, 50 + (nm - rh1)), Point(step*(i + 1), 50 + (nm - rh2)), Scalar(0, 0, 255), 2, 8, 0);
	}

	imshow("result",result);

	//直方图均衡化，均衡亮度通道 ，增加对比度，暴露更多的差异，缺点背景噪声增加，有用信号减少。
	//用 yuv格式 
	Mat result1;
	// Convert BGR image to YCbCr
	Mat ycrcb;
	cvtColor(canvas, ycrcb, COLOR_BGR2YCrCb);

	// Split image into channels
	vector<Mat> channels;
	split(ycrcb, channels);

	// Equalize the Y channel only
	equalizeHist(channels[0], channels[0]);

	// Merge the result channels
	merge(channels, ycrcb);

	// Convert color ycrcb to BGR
	cvtColor(ycrcb, result1, COLOR_YCrCb2BGR);
	// Show image
	imshow("canvas", canvas);

	// Show image
	imshow("Equalized", result1);


	//卷积 框越大 越模糊，Size(3*3) 卷积核 贸定点 Point(-1, -1) 是中间位置，右上角是0,0

	waitKey(0);
	destroyAllWindows();
	return 0;
}
int otherHist() {
	//【1】读取原图并显示
	Mat srcImage = imread("D://images/flower.png", 0);
	imshow("原图：", srcImage);
	if (!srcImage.data) {
		cout << "fail to load image" << endl;
		return 0;
	}

}