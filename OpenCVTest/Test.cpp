#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;


IplImage* templ = 0;
int i = 0;


void FindPartial(IplImage *image) {
	// ������
	char* filename2 = "../data/templ.bmp";
	printf("[i] template: %s\n", filename2);

	templ = cvLoadImage(filename2, 1);
	assert(templ != 0);

	//cvNamedWindow("origianl", CV_WINDOW_AUTOSIZE);
	//cvNamedWindow("template", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Match", CV_WINDOW_AUTOSIZE);
	
	//cvNamedWindow("res", CV_WINDOW_AUTOSIZE);

	// ������ �������
	int width = templ->width;
	int height = templ->height;

	// �������� � ������
	//cvShowImage("origianl", image);
	//cvShowImage("template", templ);

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

	// �����������
	/*cvNormalize(res, res, 1, 0, CV_MINMAX);
	cvNamedWindow("res norm", CV_WINDOW_AUTOSIZE);*/
	//cvShowImage("res norm", res);

	// ������� ������� ���������������
	cvRectangle(image, cvPoint(minloc.x, minloc.y), cvPoint(minloc.x + templ->width - 1, minloc.y + templ->height - 1), CV_RGB(255, 0, 0), 1, 8);

	// ���������� �����������
	//cvShowImage("Match", image);
	char* tmp;
	char buffer[20];
	tmp=	_itoa(i, buffer,10);
	strcat(tmp,"Match.jpg");
	cvSaveImage(tmp, image);
	i++;
	//counter++;

	// ��� ������� �������
	//cvWaitKey(0);

	// ����������� �������
	//cvReleaseImage(&image);
	cvReleaseImage(&templ);
	cvReleaseImage(&res);
	cvDestroyAllWindows();

}


int main(int argc, char* argv[])
{

	VideoCapture cap(0);


	//-- ���������� ��������� ������ ������ � ������ ����� � ��������
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 960);

	Mat frame;
	int counter = 0;
	char filename[512];
	while (true) {
		cap >> frame; //-- ����������� ��������� ����

		imshow("Video", frame); //-- ���������� ���

		char c = cvWaitKey(33); //-- ���� ���� ������ �������, ����� � ���

		if (c == 27) { //-- ������ ESC, ��������� ����
			break;
		}
		else if (c == 13) { // Enter
							// ��������� ���� � ����


			sprintf(filename, "Image%d.jpg", counter);
			printf("[i] capture... %s\n", filename);
			IplImage* image2 = cvCloneImage(&(IplImage)frame);
			//cvSaveImage(filename, image2);
			
			counter++;
			/*cvNamedWindow("origianl", CV_WINDOW_AUTOSIZE);
			cvShowImage("origianl", image2);*/
			
			
			FindPartial(image2);
		}

	}


	return 0;


	/*// �������� ����� ������������ ������
	CvCapture* capture = cvCreateCameraCapture(CV_CAP_ANY); //cvCaptureFromCAM( 0 );
	assert(capture);

	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH,1280); 
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 960); 

	// ������ ������ � ������ �����
	double width = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
	double height = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
	printf("[i] %.0f x %.0f\n", width, height);

	IplImage* frame = 0;

	cvNamedWindow("capture", CV_WINDOW_AUTOSIZE);

	printf("[i] press Enter for capture image and Esc for quit!\n\n");

	int counter = 0;
	char filename[512];

	while (true) {
		// �������� ����
		frame = cvQueryFrame(capture);

		// ����������
		cvShowImage("capture", frame);

		char c = cvWaitKey(33);
		if (c == 27) { // ������ ESC
			break;
		}
		else if (c == 13) { // Enter
							// ��������� ���� � ����
			

			sprintf(filename, "Image%d.jpg", counter);
			printf("[i] capture... %s\n", filename);
			cvSaveImage(filename, frame);
			counter++;

			FindPartial(frame);
		}
	}
	// ����������� �������
	cvReleaseCapture(&capture);
	cvDestroyWindow("capture");
	return 0;*/
}


/*

IplImage* image = 0;

int main(int argc, char* argv[])
{
	// ��� �������� ������� ������ ����������
	char* filename = argc >= 2 ? argv[1] : "cat.jpg";
	// �������� ��������
	image = cvLoadImage(filename, 1);

	printf("[i] image: %s\n", filename);
	assert(image != 0);

	// ������
	char* filename2 = argc >= 3 ? argv[2] : "templ.bmp";
	printf("[i] template: %s\n", filename2);

	templ = cvLoadImage(filename2, 1);
	assert(templ != 0);

	cvNamedWindow("origianl", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("template", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Match", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("res", CV_WINDOW_AUTOSIZE);

	// ������ �������
	int width = templ->width;
	int height = templ->height;

	// �������� � ������
	cvShowImage("origianl", image);
	cvShowImage("template", templ);

	// ����������� ��� �������� ���������� ���������
	// ������ ����������: ���� image WxH � templ wxh, �� result = (W-w+1)x(H-h+1)
	IplImage *res = cvCreateImage(cvSize((image->width - templ->width + 1), (image->height - templ->height + 1)), IPL_DEPTH_32F, 1);

	// ��������� ����������� � ��������
	cvMatchTemplate(image, templ, res, CV_TM_SQDIFF);

	// ������� ��� ��������
	cvShowImage("res", res);

	// ����������� ������ ��������� ��� ���������
	// (����� ��������� � ���������� �� �����������)
	double    minval, maxval;
	CvPoint    minloc, maxloc;
	cvMinMaxLoc(res, &minval, &maxval, &minloc, &maxloc, 0);

	// �����������
	cvNormalize(res, res, 1, 0, CV_MINMAX);
	cvNamedWindow("res norm", CV_WINDOW_AUTOSIZE);
	cvShowImage("res norm", res);

	// ������� ������� ���������������
	cvRectangle(image, cvPoint(minloc.x, minloc.y), cvPoint(minloc.x + templ->width - 1, minloc.y + templ->height - 1), CV_RGB(255, 0, 0), 1, 8);

	// ���������� �����������
	cvShowImage("Match", image);

	IplImage* frame = 0;
	frame = cvQueryFrame(capture);
	//sprintf(filename, "Image%d.jpg", counter);
	printf("[i] capture... %s\n", "Match");
	cvSaveImage("Match", image);
	//counter++;

	// ��� ������� �������
	cvWaitKey(0);

	// ����������� �������
	cvReleaseImage(&image);
	cvReleaseImage(&templ);
	cvReleaseImage(&res);
	cvDestroyAllWindows();
	return 0;
}*/