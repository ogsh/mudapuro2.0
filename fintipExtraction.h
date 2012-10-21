#ifndef __FINTIPEXTRACTION__
#define __FINTIPEXTRACTION__

#include "common.h"
#include "vector.h"
#include "finger.h"

#define MAX_NUM_LABEL 100;

public class FintipExtraction {
public:
	FintipExtraction();
	~FintipExtraction();
	std::vector<Vector2>& Get(cv::Mat& imgMask);
private:
	std::vector<Vector2> finPos;

	void erode(int* contour, int size, int itr);
	void dilate(int* contour, int size, int itr);
};

#endif