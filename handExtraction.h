#ifndef __HAND_EXTRACTION__
#define __HAND_EXTRACTION__

#include "common.h"

public class HandExtraction {
public:
	virtual ~HandExtraction(){}
	virtual cv::Mat& Extract(cv::Mat& img, cv::Mat_<unsigned short>& depth)=0;
	virtual cv::Mat& ImgMask()=0;
	virtual cv::Mat& ImgHand()=0;
};

#endif