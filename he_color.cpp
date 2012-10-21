#include "he_color.h"

HE_color::HE_color(int width, int height) {
	this->imgMask = cv::Mat(height, width, CV_8UC1);
	this->imgHand = cv::Mat(height, width, CV_8UC3);
}

HE_color::~HE_color() {
	this->imgHand.release();
	this->imgMask.release();
}

cv::Mat& HE_color::Extract(cv::Mat &img, cv::Mat_<unsigned short>& depth) {
	cv::GaussianBlur(img, img, cv::Size(9, 9), 1.0);
/*
	cv::imshow("gas", img);
	cv::Mat tmp;
	cv::Mat splitChannels[3];
	cv::cvtColor(img, tmp, CV_BGR2HSV);
	cv::split(tmp, splitChannels);

	cv::Mat imgH = splitChannels[0];
	this->imgMask.setTo(0);
	for(int j=0; j < imgH.rows; j++) {
		for(int i=0; i < imgH.cols; i++) {
			uchar color = imgH.at<uchar>(j, i);
			if(color > 0 && color < 20) {
				imgMask.at<uchar>(j, i) = 255;
			}
		}
	}
*/

	for(int j=0; j < depth.rows; j++) {
		for(int i=0; i < depth.cols; i++) {
			unsigned short val = depth(j, i);
			if(val < 800 && val > 100)
				imgMask.at<uchar>(j, i) = 255;

			else
				imgMask.at<uchar>(j, i) = 0;
		}
	}

	cv::erode(imgMask, imgMask, cv::Mat(), cv::Point(-1, -1), 2);
	cv::dilate(imgMask, imgMask, cv::Mat(), cv::Point(-1, -1), 2);
	cv::dilate(imgMask, imgMask, cv::Mat(), cv::Point(-1, -1), 2);
	cv::erode(imgMask, imgMask, cv::Mat(), cv::Point(-1, -1), 2);
	img.copyTo(this->imgHand, this->imgMask);

//	cv::imshow("he", this->imgMask);

	return this->imgHand;
}

cv::Mat& HE_color::ImgMask() {
	return this->imgMask;
}

cv::Mat& HE_color::ImgHand() {
	return this->imgHand;
}