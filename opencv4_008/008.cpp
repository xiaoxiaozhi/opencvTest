#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
int otherHist();
void histMatch();
void histMatch1();
void orb_features(Mat &gray, vector<KeyPoint> &keypionts, Mat &descriptions)
{
	Ptr<ORB> orb = ORB::create(1000, 1.2f);
	orb->detect(gray, keypionts);
	orb->compute(gray, keypionts, descriptions);
}
//均衡的结果是图像对比度的增加。均衡能够使对比度较低的局部区域获得高对比度，从而分散最频繁的强度。当图像非常暗或者非常亮，并且背景和前景之间存在非常小的差异时，此方法非常有用。通过使用直方图均衡化，可以增加对比度，并提升暴露过度或暴露不足的细节。该技术在医学图像（例如X射线）中非常有用。
int main(int arg, char** argv) {
	/*Mat canvas = imread("D://images/flat11.jpg", IMREAD_COLOR);
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
	calcHist(&mm[0], 1, 0, Mat(), b_hist, 1, &histSize, &histranges, true, false);
	calcHist(&mm[1], 1, 0, Mat(), g_hist, 1, &histSize, &histranges, true, false);
	calcHist(&mm[2], 1, 0, Mat(), r_hist, 1, &histSize, &histranges, true, false);

	Mat result = Mat::zeros(Size(600, 400), CV_8UC3);
	int margin = 50;
	int nm = result.rows - 2 * margin;
	//
	normalize(b_hist, b_hist,
		0,//均衡化最小值
		nm,//均衡化最大值
		NORM_MINMAX,//归一化所用的计算公式
		-1, Mat());
	normalize(g_hist, g_hist, 0, nm, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, nm, NORM_MINMAX, -1, Mat());

	float step = 500 / 256.0;
	for (int i = 0; i < 255; i++)
	{
		float bh1 = b_hist.at<float>(i, 0);
		float bh2 = b_hist.at<float>(i + 1, 0);
		line(result, Point(step*i, 50 + (nm - bh1)), Point(step*(i + 1), 50 + (nm - bh2)), Scalar(255, 0, 0), 2, 8, 0);

		float gh1 = g_hist.at<float>(i, 0);
		float gh2 = g_hist.at<float>(i + 1, 0);
		line(result, Point(step*i, 50 + (nm - gh1)), Point(step*(i + 1), 50 + (nm - gh2)), Scalar(0, 255, 0), 2, 8, 0);

		float rh1 = r_hist.at<float>(i, 0);
		float rh2 = r_hist.at<float>(i + 1, 0);
		line(result, Point(step*i, 50 + (nm - rh1)), Point(step*(i + 1), 50 + (nm - rh2)), Scalar(0, 0, 255), 2, 8, 0);
	}

	imshow("result", result);

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
	*/
	histMatch1();
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
//直方图均衡化后可以改变直方图分布形式，但是不能指定。 
void histMatch() {
	Mat img = imread("flatNight.jpg");
	Mat temp = imread("flatNightPart.jpg");
	if (img.empty() || temp.empty())
	{
		cout << "请确认图像文件名称是否正确" << endl;
		return;
	}
	Mat result;
	matchTemplate(img, temp, result, TM_CCOEFF_NORMED);//模板匹配
	double maxVal, minVal;
	Point minLoc, maxLoc;
	//寻找匹配结果中的最大值和最小值以及坐标位置
	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
	//绘制最佳匹配区域
	rectangle(img, cv::Rect(maxLoc.x, maxLoc.y, temp.cols, temp.rows), Scalar(0, 0, 255), 2);
	imshow("原图", img);
	imshow("模板图像", temp);
	imshow("result", result);
}

void histMatch1() {

	Mat img1, img2;
	img1 = imread("flatNight.jpg");
	img2 = imread("flatPart2.jpg");

	if (!(img1.data && img2.dataend))
	{
		cout << "读取图像错误，请确认图像文件是否正确" << endl;
		return;
	}

	//提取ORB特征点
	vector<KeyPoint> Keypoints1, Keypoints2;
	Mat descriptions1, descriptions2;

	//计算SURF特征点
	orb_features(img1, Keypoints1, descriptions1);
	orb_features(img2, Keypoints2, descriptions2);

	//判断描述子数据类型，如果数据类型不符需要进行类型转换，主要针对ORB特征点
	if ((descriptions1.type() != CV_32F) && (descriptions2.type() != CV_32F))
	{
		descriptions1.convertTo(descriptions1, CV_32F);
		descriptions2.convertTo(descriptions2, CV_32F);
	}

	//特征点匹配
	vector<DMatch> matches;  //定义存放匹配结果的变量
	FlannBasedMatcher matcher;  //使用默认值即可
	matcher.match(descriptions1, descriptions2, matches);
	cout << "matches=" << matches.size() << endl;  //匹配成功特征点数目


												   //寻找距离最大值和最小值，如果是ORB特征点min_dist取值需要大一些
	double max_dist = 0; double min_dist = 100;
	for (int i = 0; i < descriptions1.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}
	cout << " Max dist :" << max_dist << endl;
	cout << " Min dist :" << min_dist << endl;

	//将最大值距离的0.4倍作为最优匹配结果进行筛选
	std::vector< DMatch > good_matches;
	for (int i = 0; i < descriptions1.rows; i++)
	{
		if (matches[i].distance < 0.40 * max_dist)
		{
			good_matches.push_back(matches[i]);
		}
	}
	cout << "good_matches=" << good_matches.size() << endl;  //匹配成功特征点数目

															 //绘制匹配结果
	Mat outimg, outimg1;
	drawMatches(img1, Keypoints1, img2, Keypoints2, matches, outimg);
	drawMatches(img1, Keypoints1, img2, Keypoints2, good_matches, outimg1);
	imshow("未筛选结果", outimg);
	imshow("筛选结果", outimg1);
}