#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;


IplImage* templ = 0;
int i = 0;


void FindingObjectsWithoutSlope(IplImage *image) {
	// шаблон
	char* filename2 = "../data/templ.bmp";
	printf("[i] template: %s\n", filename2);

	templ = cvLoadImage(filename2, 1);
	assert(templ != 0);

	cvNamedWindow("Match", CV_WINDOW_AUTOSIZE);

	//cvNamedWindow("res", CV_WINDOW_AUTOSIZE);

	// размер шаблона
	int width = templ->width;
	int height = templ->height;
	// изображение для хранения результата сравнения
	// размер результата: если image WxH и templ wxh, то result = (W-w+1)x(H-h+1)
	IplImage *res = cvCreateImage(cvSize((image->width - templ->width + 1), (image->height - templ->height + 1)), IPL_DEPTH_32F, 1);

	// сравнение изображения с шаблоном
	cvMatchTemplate(image, templ, res, CV_TM_SQDIFF);

	// покажем что получили
	//cvShowImage("res", res);

	// определение лучшее положение для сравнения
	// (поиск минимумов и максимумов на изображении)
	double    minval, maxval;
	CvPoint    minloc, maxloc;
	cvMinMaxLoc(res, &minval, &maxval, &minloc, &maxloc, 0);

	// выделим область прямоугольником
	cvRectangle(image, cvPoint(minloc.x, minloc.y), cvPoint(minloc.x + templ->width - 1, minloc.y + templ->height - 1), CV_RGB(255, 0, 0), 1, 8);

	// показываем изображение
	//cvShowImage("Match", image);
	char* tmp;
	char buffer[20];
	tmp = _itoa(i, buffer, 10);
	strcat(tmp, "Match.jpg");
	cvSaveImage(tmp, image);
	i++;
	// ждём нажатия клавиши
	//cvWaitKey(0);

	// освобождаем ресурсы
	cvReleaseImage(&templ);
	cvReleaseImage(&res);
	cvDestroyAllWindows();

}

