#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

void FindingObjectAtAngle(IplImage *image, int i);
void ComparisonObjectsByMomentsOfTheirContours();
int FindColor();
void SearchOfFiguresByColor();

//void FindingObjectsWithoutSlope(IplImage *image);



int main(int argc, char* argv[])
{
	SearchOfFiguresByColor();
	ComparisonObjectsByMomentsOfTheirContours();
	//ComparisonObjectsByMomentsOfTheirContours();
	
	//VideoCapture cap(0);

	////-- ���������� ��������� ������ ������ � ������ ����� � ��������
	//cap.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
	//cap.set(CV_CAP_PROP_FRAME_HEIGHT, 960);

	//Mat frame;
	//int counter = 0;
	//int i = 0;
	//char filename[512];
	//while (true) {
	//	cap >> frame; //-- ����������� ��������� ����

	//	imshow("Video", frame); //-- ���������� ���
	//	char c = cvWaitKey(33); //-- ���� ���� ������ �������, ����� � ���

	//	if (i == 30) {
	//		sprintf(filename, "Image%d.jpg", counter);
	//		printf("[i] capture... %s\n", filename);
	//		IplImage* image2 = cvCloneImage(&(IplImage)frame);

	//		
	//		FindingObjectAtAngle(image2, counter);
	//		counter++;
	//		i = 0;
	//	}
	//	i++;
	//}



	return 0;
}