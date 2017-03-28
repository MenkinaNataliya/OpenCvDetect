#include "opencv2/core/core_c.h"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/highgui/highgui_c.h"


void DrawRotatedRect(IplImage * iplSrc, CvBox2D rect, CvScalar color, int thickness, int line_type = 8, int shift = 0)
{
	CvPoint2D32f boxPoints[4];
	cvBoxPoints(rect, boxPoints);
	cvLine(iplSrc, cvPoint((int)boxPoints[0].x, (int)boxPoints[0].y), cvPoint((int)boxPoints[1].x, (int)boxPoints[1].y), color, thickness, line_type, shift);
	cvLine(iplSrc, cvPoint((int)boxPoints[1].x, (int)boxPoints[1].y), cvPoint((int)boxPoints[2].x, (int)boxPoints[2].y), color, thickness, line_type, shift);
	cvLine(iplSrc, cvPoint((int)boxPoints[2].x, (int)boxPoints[2].y), cvPoint((int)boxPoints[3].x, (int)boxPoints[3].y), color, thickness, line_type, shift);
	cvLine(iplSrc, cvPoint((int)boxPoints[3].x, (int)boxPoints[3].y), cvPoint((int)boxPoints[0].x, (int)boxPoints[0].y), color, thickness, line_type, shift);
}



void FindingObjectAtAngle(IplImage *image, int i)//http://recog.ru/blog/opencv/229.html
{
	
	//IplImage *image = cvLoadImage("../data/image2.jpg"); // 24-битное изображений
	IplImage *gray = cvCreateImage(cvGetSize(image), 8, 1); // ѕустое 8-битное изображение

	cvCvtColor(image, gray, CV_BGR2GRAY); // ѕеревод в градации серого
	cvThreshold(gray, gray, 128, 255, CV_THRESH_BINARY_INV); // Ѕинаризаци€

	//cvSaveImage("../data/binary1.png", gray);

	CvMemStorage* storage = cvCreateMemStorage(0);

	CvSeq* contours = 0;
	cvFindContours(gray, storage, &contours, sizeof(CvContour),
		CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0)); // ѕоиск контуров 

	//for (CvSeq* c = contours; c != NULL; c = c->h_next)
	//{
	//	CvRect Rect = cvBoundingRect(c); // ѕоиск ограничивающего пр€моугольника
	//	if (Rect.width < 50) continue; // ћаленькие контуры меньше 50 пикселей не нужны

	//	//cvRectangle(image, cvPoint(Rect.x, Rect.y), cvPoint(Rect.x + Rect.width, Rect.y + Rect.height), CV_RGB(255, 0, 0), 2); 
	//	CvBox2D b = cvMinAreaRect2(c);
	//	DrawRotatedRect(image, b, CV_RGB(255, 0, 0), 2);

	//}
	cvApproxPoly(contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, 3, 1);
	cvDrawContours(image, contours, CV_RGB(255, 0, 0), CV_RGB(0, 255, 0), 2, 1, CV_AA, cvPoint(0, 0));

	cvReleaseMemStorage(&storage);

	char str[100];
	strcpy(str, "../data/image");                // скопировать строку "Ёти" в str
	char* tmp;
	char buffer[20];
	tmp = _itoa(i, buffer, 10);
										// добавить к строке str строку, передаваемую во втором параметре
	strcat(str, tmp);
	strcat(str, ".png");

	cvSaveImage(str, image);

	cvReleaseImage(&image);
	cvReleaseImage(&gray);
	
}