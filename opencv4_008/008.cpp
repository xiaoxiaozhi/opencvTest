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
//����Ľ����ͼ��Աȶȵ����ӡ������ܹ�ʹ�ԱȶȽϵ͵ľֲ������ø߶Աȶȣ��Ӷ���ɢ��Ƶ����ǿ�ȡ���ͼ��ǳ������߷ǳ��������ұ�����ǰ��֮����ڷǳ�С�Ĳ���ʱ���˷����ǳ����á�ͨ��ʹ��ֱ��ͼ���⻯���������ӶԱȶȣ���������¶���Ȼ�¶�����ϸ�ڡ��ü�����ҽѧͼ������X���ߣ��зǳ����á�
int main(int arg, char** argv) {
	/*Mat canvas = imread("D://images/flat11.jpg", IMREAD_COLOR);
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
	calcHist(&mm[0], 1, 0, Mat(), b_hist, 1, &histSize, &histranges, true, false);
	calcHist(&mm[1], 1, 0, Mat(), g_hist, 1, &histSize, &histranges, true, false);
	calcHist(&mm[2], 1, 0, Mat(), r_hist, 1, &histSize, &histranges, true, false);

	Mat result = Mat::zeros(Size(600, 400), CV_8UC3);
	int margin = 50;
	int nm = result.rows - 2 * margin;
	//
	normalize(b_hist, b_hist,
		0,//���⻯��Сֵ
		nm,//���⻯���ֵ
		NORM_MINMAX,//��һ�����õļ��㹫ʽ
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
	*/
	histMatch1();
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
//ֱ��ͼ���⻯����Ըı�ֱ��ͼ�ֲ���ʽ�����ǲ���ָ���� 
void histMatch() {
	Mat img = imread("flatNight.jpg");
	Mat temp = imread("flatNightPart.jpg");
	if (img.empty() || temp.empty())
	{
		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;
		return;
	}
	Mat result;
	matchTemplate(img, temp, result, TM_CCOEFF_NORMED);//ģ��ƥ��
	double maxVal, minVal;
	Point minLoc, maxLoc;
	//Ѱ��ƥ�����е����ֵ����Сֵ�Լ�����λ��
	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
	//�������ƥ������
	rectangle(img, cv::Rect(maxLoc.x, maxLoc.y, temp.cols, temp.rows), Scalar(0, 0, 255), 2);
	imshow("ԭͼ", img);
	imshow("ģ��ͼ��", temp);
	imshow("result", result);
}

void histMatch1() {

	Mat img1, img2;
	img1 = imread("flatNight.jpg");
	img2 = imread("flatPart2.jpg");

	if (!(img1.data && img2.dataend))
	{
		cout << "��ȡͼ�������ȷ��ͼ���ļ��Ƿ���ȷ" << endl;
		return;
	}

	//��ȡORB������
	vector<KeyPoint> Keypoints1, Keypoints2;
	Mat descriptions1, descriptions2;

	//����SURF������
	orb_features(img1, Keypoints1, descriptions1);
	orb_features(img2, Keypoints2, descriptions2);

	//�ж��������������ͣ�����������Ͳ�����Ҫ��������ת������Ҫ���ORB������
	if ((descriptions1.type() != CV_32F) && (descriptions2.type() != CV_32F))
	{
		descriptions1.convertTo(descriptions1, CV_32F);
		descriptions2.convertTo(descriptions2, CV_32F);
	}

	//������ƥ��
	vector<DMatch> matches;  //������ƥ�����ı���
	FlannBasedMatcher matcher;  //ʹ��Ĭ��ֵ����
	matcher.match(descriptions1, descriptions2, matches);
	cout << "matches=" << matches.size() << endl;  //ƥ��ɹ���������Ŀ


												   //Ѱ�Ҿ������ֵ����Сֵ�������ORB������min_distȡֵ��Ҫ��һЩ
	double max_dist = 0; double min_dist = 100;
	for (int i = 0; i < descriptions1.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}
	cout << " Max dist :" << max_dist << endl;
	cout << " Min dist :" << min_dist << endl;

	//�����ֵ�����0.4����Ϊ����ƥ��������ɸѡ
	std::vector< DMatch > good_matches;
	for (int i = 0; i < descriptions1.rows; i++)
	{
		if (matches[i].distance < 0.40 * max_dist)
		{
			good_matches.push_back(matches[i]);
		}
	}
	cout << "good_matches=" << good_matches.size() << endl;  //ƥ��ɹ���������Ŀ

															 //����ƥ����
	Mat outimg, outimg1;
	drawMatches(img1, Keypoints1, img2, Keypoints2, matches, outimg);
	drawMatches(img1, Keypoints1, img2, Keypoints2, good_matches, outimg1);
	imshow("δɸѡ���", outimg);
	imshow("ɸѡ���", outimg1);
}