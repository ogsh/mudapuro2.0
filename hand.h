#ifndef __HAND__
#define __HAND__

#include "he_color.h"
#include "fintipExtraction.h"
#include "finger.h"

public class Hand {
public:
	Hand(int imgWidth, int imgHeight);
	~Hand();
	void Get(cv::Mat& img, cv::Mat_<unsigned short>& depth);
	void Initialize();
	cv::Mat& DrawStatus(cv::Mat& img);

private:
	int imgWidth;
	int imgHeight;
	int num_fingers;
	static const int MAX_NUM_FINGERS = 5;
	Vector2 pos;

	HandExtraction* he;
	FintipExtraction* fe;

	std::vector<Finger> fingers;
};

#endif