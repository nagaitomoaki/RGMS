#include <Windows.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include "monsterstrike.h"

MonsterStrike::MonsterStrike() {
	//read template image 

	std::cout << "initialize" << std::endl;
}

MonsterStrike::~MonsterStrike() {
	//finish 

}

templateImg::templateImg() {
	ok = cv::imread("ok.bmp", 1);
}

templateImg::~templateImg() {

}

void MonsterStrike::proceedStory() {
	HWND  frameHandle = FindWindow(TEXT("LDPlayerMainFrame"), TEXT("LDPlayer"));
	HWND screenHandle = FindWindowEx(frameHandle, 0, TEXT("RenderWindow"), 0);
	if (screenHandle) {
		int2 position;
		getScreenImage(screenHandle);
		//Name
		//OK
		//Battle
		//Agree
		//Download
		//No Found
		//Box Found
		//Goggle Found
		matchingImage(templateImg.ok,0.8, position);
		clickMessage(screenHandle,position);
	}
}

void MonsterStrike::battle() {
	//proceed battle 
}

void MonsterStrike::saveData(){
	//savae data to disk
}

void MonsterStrike::clickMessage(const HWND& handle, const int2& position) {
	PostMessage(handle, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(position.x, position.y));
	Sleep(200);
	PostMessage(handle, WM_LBUTTONUP, 0, MAKELPARAM(position.x, position.y));
	Sleep(200);
}

void MonsterStrike::matchingImage(const cv::Mat& tmp, const float& threshold, int2& position) {
	//find image
	cv::Mat result;
	cv::matchTemplate(screen, tmp, result, cv::TM_CCORR_NORMED);

	//calculate center position on matching image 
	cv::Rect roi_rect(0, 0, tmp.cols, tmp.rows);
	cv::Point maxpt;
	double maxVal;
	minMaxLoc(result, 0, &maxVal, 0, &maxpt);
	if (maxVal > threshold) {
		roi_rect.x = maxpt.x;
		roi_rect.y = maxpt.y;
		position.x = maxpt.x + tmp.cols / 2;
		position.y = maxpt.y + tmp.rows / 2;
		rectangle(screen, roi_rect, cv::Scalar(0, 255, 255), 1);
	}
	else {
		position.x = 0;
		position.y = 0;
	}
	cv::imwrite("screen.jpg", screen);
}

void MonsterStrike::getState() {
	//realize situation 
}

void MonsterStrike::getScreenImage(const HWND& handle) {
	HDC hwindowDC, hwindowCompatibleDC;

	int height, width, srcheight, srcwidth;
	HBITMAP hbwindow;
	cv::Mat src;
	BITMAPINFOHEADER  bi;

	hwindowDC = GetDC(handle);
	hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
	SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);

	// get the height and width of the screen
	RECT windowsize;
	GetClientRect(handle, &windowsize);

	srcheight = windowsize.bottom;
	srcwidth = windowsize.right;
	height = windowsize.bottom;
	width = windowsize.right;

	src.create(height, width, CV_8UC4);

	// create a bitmap
	hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
	bi.biSize = sizeof(BITMAPINFOHEADER); 
	bi.biWidth = width;
	bi.biHeight = -height;  //this is the line that makes it draw upside down or not
	bi.biPlanes = 1; //The number of planes for the target device.This value must be set to 1
	bi.biBitCount = 32; //The number of bits - per - pixe 32 or 16 bit per pixel
	bi.biCompression = BI_RGB; //The type of compression for a compressed bottom - up bitmap
	bi.biSizeImage = 0;//The size, in bytes, of the image. This may be set to zero for BI_RGB bitmaps.
	bi.biXPelsPerMeter = 0; //The horizontal resolution, in pixels - per - meter,
	bi.biYPelsPerMeter = 0;//The vertical resolution
	bi.biClrUsed = 0;//The number of color indexes in the color table that are actually used by the bitmap. 
	bi.biClrImportant = 0;//The number of color indexes that are required for displaying the bitmap. 

	// use the previously created device context with the bitmap
	SelectObject(hwindowCompatibleDC, hbwindow);

	// copy from the window device context to the bitmap device context
	StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, 0, 0, srcwidth, srcheight, SRCCOPY); //change SRCCOPY to NOTSRCCOPY for wacky colors !
	GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, src.data, (BITMAPINFO *)&bi, DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow
	DeleteObject(hbwindow); DeleteDC(hwindowCompatibleDC); ReleaseDC(handle, hwindowDC);

	//32bitÅ®24bit(4channelÅ®3channel)
	std::vector<cv::Mat> planes;
	split(src, planes);
	std::vector<cv::Mat> color_shuffle;
	color_shuffle.push_back(planes[0]);
	color_shuffle.push_back(planes[1]);
	color_shuffle.push_back(planes[2]);
	cv::merge(color_shuffle, screen);
}