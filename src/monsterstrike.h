#pragma once
#include <Windows.h>
#include <opencv2/opencv.hpp>

class int2 {
public:
	int x = 0;
	int y = 0;
};

class templateImg {
public:
	templateImg();
	~templateImg();
	cv::Mat ok;
	cv::Mat agree;
	cv::Mat battle;
	cv::Mat name;
	cv::Mat download;
	cv::Mat goggle;
	cv::Mat no;
	cv::Mat box;
};

class MonsterStrike{
public:
	MonsterStrike();
	~MonsterStrike();
	void proceedStory();
	void saveData();
private:
	unsigned char state;
	unsigned char starCount;
	cv::Mat screen;
	templateImg templateImg;
	void battle();
	void clickMessage(const HWND& hwnd, const int2& position);
	void matchingImage(const cv::Mat& tmp, const float& threshold, int2& position);
	void getState();
	void getScreenImage(const HWND& handle);
};
