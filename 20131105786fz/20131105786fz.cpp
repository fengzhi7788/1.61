#include "stdafx.h"
#include <opencv2/opencv.hpp>  
#include <cstdio>  
#include <cstdlib>  
#include <Windows.h>  
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\video\background_segm.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
	const char *pstrImageName = "qq.jpg";
	//IplImage *pSrcImage = cvLoadImage(pstrImageName, 0);
	IplImage *img = cvLoadImage(pstrImageName, CV_LOAD_IMAGE_COLOR);
	//Mat picture(pSrcImage);
	if(!img)
	{
		printf("can't load ");
		return -1;
	}
	const char *pstrCascadeFileName = "haarcascade_frontalface_alt.xml";
	CvHaarClassifierCascade *pHaarCascade = NULL;
	pHaarCascade = (CvHaarClassifierCascade*)cvLoad(pstrCascadeFileName);
	if (pHaarCascade != NULL)
	{		
		DWORD dwTimeBegin, dwTimeEnd;  
		dwTimeBegin = GetTickCount(); 
		CvMemStorage *pcvMStorage = cvCreateMemStorage(0);
		CvSeq *pcvSeqFaces = cvHaarDetectObjects(img, pHaarCascade, pcvMStorage);
		dwTimeEnd = GetTickCount();
		printf("人脸个数: %d   识别用时: %d ms\n", pcvSeqFaces->total, dwTimeEnd - dwTimeBegin);  
		// 标记
		for(int i = 0; i <pcvSeqFaces->total; i++)
		{
			CvRect* r = (CvRect*)cvGetSeqElem(pcvSeqFaces, i);	
			CvPoint center;
			int radius;
			center.x = cvRound((r->x + r->width * 0.5));
			center.y = cvRound((r->y + r->height * 0.5));
			radius = cvRound((r->width + r->height) * 0.25);
			printf("Found a face at (%d, %d)\n", center.x, center.y);
			cvCircle(img, center, radius, cvScalar(255,255,255));
			//ellipse(picture, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(0, 0, 255),5, 2, 0);
		}
		cvReleaseMemStorage(&pcvMStorage);
	}
	cvNamedWindow("face detection", CV_WINDOW_AUTOSIZE);
	cvShowImage("face detection", img);
	cvWaitKey(0);
	cvDestroyAllWindows();
	cvReleaseImage(&img);	
}