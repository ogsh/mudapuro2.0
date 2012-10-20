#ifndef __KINECT__
#define __KINECT__

#include <XnCppWrapper.h>
#include "common.h"

#pragma comment(lib,"C:/OpenNI/Lib/openNI.lib")

#define CONFIG_PATH "config.xml"

public class Kinect {
public:
	Kinect(std::string config_path);
	~Kinect();
	void Capture();
	cv::Mat& GetColorImage();
	cv::Mat& GetDepthImage();
	cv::Mat_<unsigned short>& Depth();
private:
	int cImgWidth;
	int cImgHeight;
	int dImgWidth;
	int dImgHeight;

	xn::Context context;
	xn::EnumerationErrors errors;
	xn::DepthGenerator depthGnt;
	xn::ImageGenerator imageGnt;
	xn::DepthMetaData depthMD;
	xn::ImageMetaData imageMD;

	cv::Mat cImg;
	cv::Mat dImg;

	cv::Mat_<unsigned short> depth;
	cv::Mat img;
};

#endif