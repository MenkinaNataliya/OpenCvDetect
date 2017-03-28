#include "opencv\cv.h"
#include "opencv\highgui.h"
#include <stdlib.h>
#include <stdio.h>

void ComparisonObjectsByMomentsOfTheirContours();



void SearchOfFiguresByColor() {//http://robocraft.ru/blog/computervision/365.html

	IplImage* image = 0;


	// для хранения каналов RGB
	IplImage* rgb = 0;
	IplImage* r_plane = 0;
	IplImage* g_plane = 0;
	IplImage* b_plane = 0;
	// для хранения каналов RGB после преобразования
	IplImage* r_range = 0;
	IplImage* g_range = 0;
	IplImage* b_range = 0;
	// для хранения суммарной картинки
	IplImage* rgb_and = 0;

	int Rmin = 0;
	int Rmax = 256;

	int Gmin = 0;
	int Gmax = 256;

	int Bmin = 0;
	int Bmax = 256;

	int RGBmax = 256;

/*---------------------------------------------------разбор цвета шаблона ------------------------------*/
	char* filenameTempl = "../data/templ3.bmp";
	// получаем шаблон
	image = cvLoadImage(filenameTempl, 1);


	rgb = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 3);
	r_plane = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	g_plane = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	b_plane = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	//  копируем
	cvCopy(image, rgb);
	// разбиваем на отельные каналы
	cvSplit(rgb, b_plane, g_plane, r_plane, 0);


	double framemin = 0;
	double framemax = 0;
	// получаем цвет шаблона (подразумевается что он один)
	cvMinMaxLoc(r_plane, &framemin, &framemax);
	Rmin = framemin;
	Rmax = framemax;
	cvMinMaxLoc(g_plane, &framemin, &framemax);
	Gmin = framemin;
	Gmax = framemax;
	cvMinMaxLoc(b_plane, &framemin, &framemax);
	Bmin = framemin;
	Bmax = framemax;
/*------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------Работа с основной картинкой------------------------------*/

	char* filename = "../data/image2.bmp";

	image = cvLoadImage(filename, 1);

	printf("[i] image: %s\n", filename);
	assert(image != 0);

	// создаём картинки
	rgb = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 3);
	r_plane = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	g_plane = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	b_plane = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	r_range = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	g_range = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	b_range = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	rgb_and = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	//  копируем
	cvCopy(image, rgb);
	// разбиваем на отельные каналы
	cvSplit(rgb, b_plane, g_plane, r_plane, 0);

	cvNamedWindow("rgb and", CV_WINDOW_AUTOSIZE);
	
	cvInRangeS(r_plane, cvScalar(Rmin), cvScalar(255), r_range);
	cvInRangeS(g_plane, cvScalar(Gmin), cvScalar(Gmin), g_range);
	cvInRangeS(b_plane, cvScalar(Bmin), cvScalar(Bmin), b_range);
	cvAnd(r_range, g_range, rgb_and);
	cvAnd(rgb_and, b_range, rgb_and);
	cvShowImage("rgb and", rgb_and);
	cvSaveImage("../data/find.bmp", rgb_and);

/*------------------------------------------------------------------------------------------------------------*/


// освобождаем ресурсы
	cvReleaseImage(&image);
	cvReleaseImage(&rgb);
	cvReleaseImage(&r_plane);
	cvReleaseImage(&g_plane);
	cvReleaseImage(&b_plane);
	cvReleaseImage(&r_range);
	cvReleaseImage(&g_range);
	cvReleaseImage(&b_range);
	cvReleaseImage(&rgb_and);
	// удаляем окна
	cvDestroyAllWindows();
}