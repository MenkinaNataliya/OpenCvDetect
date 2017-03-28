#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;


IplImage* templ = 0;
int i = 0;


void FindingObjectsWithoutSlope(IplImage *image) {
	// ������
	char* filename2 = "../data/templ.bmp";
	printf("[i] template: %s\n", filename2);

	templ = cvLoadImage(filename2, 1);
	assert(templ != 0);

	cvNamedWindow("Match", CV_WINDOW_AUTOSIZE);

	//cvNamedWindow("res", CV_WINDOW_AUTOSIZE);

	// ������ �������
	int width = templ->width;
	int height = templ->height;
	// ����������� ��� �������� ���������� ���������
	// ������ ����������: ���� image WxH � templ wxh, �� result = (W-w+1)x(H-h+1)
	IplImage *res = cvCreateImage(cvSize((image->width - templ->width + 1), (image->height - templ->height + 1)), IPL_DEPTH_32F, 1);

	// ��������� ����������� � ��������
	cvMatchTemplate(image, templ, res, CV_TM_SQDIFF);

	// ������� ��� ��������
	//cvShowImage("res", res);

	// ����������� ������ ��������� ��� ���������
	// (����� ��������� � ���������� �� �����������)
	double    minval, maxval;
	CvPoint    minloc, maxloc;
	cvMinMaxLoc(res, &minval, &maxval, &minloc, &maxloc, 0);

	// ������� ������� ���������������
	cvRectangle(image, cvPoint(minloc.x, minloc.y), cvPoint(minloc.x + templ->width - 1, minloc.y + templ->height - 1), CV_RGB(255, 0, 0), 1, 8);

	// ���������� �����������
	//cvShowImage("Match", image);
	char* tmp;
	char buffer[20];
	tmp = _itoa(i, buffer, 10);
	strcat(tmp, "Match.jpg");
	cvSaveImage(tmp, image);
	i++;
	// ��� ������� �������
	//cvWaitKey(0);

	// ����������� �������
	cvReleaseImage(&templ);
	cvReleaseImage(&res);
	cvDestroyAllWindows();

}

