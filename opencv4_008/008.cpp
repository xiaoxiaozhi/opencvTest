#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
int otherHist();
//����Ľ����ͼ��Աȶȵ����ӡ������ܹ�ʹ�ԱȶȽϵ͵ľֲ������ø߶Աȶȣ��Ӷ���ɢ��Ƶ����ǿ�ȡ���ͼ��ǳ������߷ǳ��������ұ�����ǰ��֮����ڷǳ�С�Ĳ���ʱ���˷����ǳ����á�ͨ��ʹ��ֱ��ͼ���⻯���������ӶԱȶȣ���������¶���Ȼ�¶�����ϸ�ڡ��ü�����ҽѧͼ������X���ߣ��зǳ����á�
int main(int arg, char** argv) {
	Mat canvas = imread("D://images/flower.png",IMREAD_COLOR);
	if (canvas.empty()) {
		printf("ͼ��Ϊ��");
		waitKey(0);
		destroyAllWindows();
		return -1;
	}
	vector<Mat> mm;
	//ͨ������
	split(canvas, mm);
	namedWindow("canvas", WINDOW_AUTOSIZE);
	printf("�����%d��ͨ��", mm.size());
	//����ֱ��ͼ
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
		0,//���⻯��Сֵ
		nm,//���⻯���ֵ
		NORM_MINMAX,//��һ�����õļ��㹫ʽ
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

	//ֱ��ͼ���⻯����������ͨ�� �����ӶԱȶȣ���¶����Ĳ��죬ȱ�㱳���������ӣ������źż��١�
	//�� yuv��ʽ 
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


	//��� ��Խ�� Խģ����Size(3*3) ����� ó���� Point(-1, -1) ���м�λ�ã����Ͻ���0,0

	waitKey(0);
	destroyAllWindows();
	return 0;
}
int otherHist() {
	//��1����ȡԭͼ����ʾ
	Mat srcImage = imread("D://images/flower.png", 0);
	imshow("ԭͼ��", srcImage);
	if (!srcImage.data) {
		cout << "fail to load image" << endl;
		return 0;
	}

}