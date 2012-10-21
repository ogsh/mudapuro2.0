#ifndef __HE_COLOR__
#define __HE_COLOR__

#include "handExtraction.h"

public class HE_color : public HandExtraction {
public:
	HE_color(int width, int height);
	~HE_color();
	cv::Mat& Extract(cv::Mat& img, cv::Mat_<unsigned short>& depth);

	cv::Mat& ImgMask();
	cv::Mat& ImgHand();
private:
	cv::Mat imgHand;
	cv::Mat imgMask;
};

#endif;