#include "kinect.h"

Kinect::Kinect(std::string config_path) {
	XnStatus rc = this->context.InitFromXmlFile((const XnChar*)config_path.c_str());

	if (rc == XN_STATUS_NO_NODE_PRESENT)
	{
		XnChar strError[1024];
		errors.ToString(strError, 1024);
		printf("%s\n", strError);
		exit(1);
	}
	else if (rc != XN_STATUS_OK)
	{
		printf("Open failed: %s\n", xnGetStatusString(rc));
		exit(1);
	}

	context.FindExistingNode(XN_NODE_TYPE_DEPTH, this->depthGnt);
	context.FindExistingNode(XN_NODE_TYPE_IMAGE, this->imageGnt);

	this->imageGnt.GetMetaData(this->imageMD);
	this->depthGnt.GetMetaData(this->depthMD);

	this->cImgWidth = this->imageMD.XRes();
	this->cImgHeight = this->imageMD.YRes();
	this->dImgWidth = this->depthMD.XRes();
	this->dImgHeight = this->depthMD.YRes();

	this->cImg = cv::Mat(this->cImgHeight, this->cImgWidth, CV_8UC3);
	this->dImg = cv::Mat(this->dImgHeight, this->dImgWidth, CV_8UC1);

	this->depth = cv::Mat_<unsigned short>(this->dImgHeight, this->dImgWidth);
	this->img = cv::Mat(this->cImgHeight, this->cImgWidth, CV_8UC3);
}

Kinect::~Kinect() {
	this->imageGnt.Release();
	this->depthGnt.Release();
	this->cImg.release();
	this->dImg.release();
	this->context.Shutdown();
}

void Kinect::Capture() {
	context.WaitAnyUpdateAll();
	this->imageGnt.GetMetaData(this->imageMD);
	this->depthGnt.GetMetaData(this->depthMD);

	this->depth.data = (unsigned char*)this->depthMD.WritableData();
	this->img.data = (unsigned char*)this->imageMD.WritableData();
}

cv::Mat_<unsigned short>& Kinect::Depth() {
	return this->depth;
}

cv::Mat& Kinect::GetColorImage() {
	cv::cvtColor(this->img, this->cImg, CV_RGB2BGR);
	return this->cImg;
}

cv::Mat& Kinect::GetDepthImage() {
	this->depth.convertTo(this->dImg, CV_8UC1, -255/4096.0, 255);
	return this->dImg;
}