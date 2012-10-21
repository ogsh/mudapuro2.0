#include "fintipExtraction.h"

FintipExtraction::FintipExtraction() {
	this->finPos = std::vector<Vector2>(0);
}

FintipExtraction::~FintipExtraction() {
}

std::vector<Vector2>& FintipExtraction::Get(cv::Mat& imgMask) {
	this->finPos.clear();
	double th_contour_length = 50;
	std::vector<std::vector<cv::Point>> contours;
	std::vector<std::vector<cv::Point>> contours_th;

	cv::findContours(imgMask, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	if(contours.size() == 0)
		return this->finPos;

	int idx = 0;
	unsigned int max_length = -1000;
	for(unsigned int i=0; i < contours.size(); i++) {
		if(contours[i].size() > max_length) {
			max_length = contours[i].size();
			idx = i;
		}
	}
	std::vector<cv::Point> contour(contours[idx].size());
	contour = contours[idx];

	if(contour.size() < 400)
		return this->finPos;

	//移動平均
	int w_size = (int)((double)contour.size() * 0.005);
	std::vector<cv::Point> sContour(contour.size());
	int length = (int)contour.size();
	for(int p=0; p < length; p++) {
		double x = 0;
		double y = 0;
		for(int w=-w_size; w < w_size; w++) {
			int idx = p + w;
			if(idx < 0) {
				int mul = (int)((-(double)idx)/(double)length) + 1;
				idx += mul * length;
			}
			else if(idx > length - 1)
				idx %= length;

			x += contour[idx].x;
			y += contour[idx].y;
		}
		sContour[p].x = (int)(x / (2 * w_size));
		sContour[p].y = (int)(y / (2 * w_size));
	}

	cv::Mat showCtr(imgMask.rows, imgMask.cols, CV_8UC1);
	showCtr.setTo(0);
	for(unsigned int c=0; c < sContour.size(); c++) {
		showCtr.at<uchar>(sContour[c].y, sContour[c].x) = 255;
	}
	cv::imshow("showCtr", showCtr);

	// === 指先どこ？ === //
	Vector2 vec[2];
	int breadth = (int)((double)length * 0.03);
	int* tips = new int[(int)sContour.size()];
	for(unsigned int p=0; p < sContour.size(); p++) {
		int idx[2] = {p - breadth, p + breadth};
		for(int i=0; i < 2; i++) {
			if(idx[i] < 0) {
				int mul = (int)((-(double)idx[i])/(double)length) + 1;
				idx[i] += mul * length;
			}
			else if(idx[i] > length - 1)
				idx[i] %= length;

			vec[i] = Vector2(sContour[p].x - sContour[idx[i]].x, sContour[p].y - sContour[idx[i]].y);
		}
		double product = vec[0].Product(vec[1]) / (vec[0].Length() * vec[1].Length());
		double oProduct = vec[0].OuterProduct(vec[1]);
		tips[p] = (product > 0.45 && oProduct > 0)? 1 : 0;
	}

	// === 縮退・拡大 === //
	this->dilate(tips, sContour.size(), 5);
	this->erode(tips, sContour.size(), 5);

	// === らべリング === //
	bool flg_nottips = false;
	int* labels = new int[sContour.size()];
	memset(labels, -1, sContour.size() * sizeof(labels));
	int num_label = -1;
	int p = 0;
	int dir[2] = {-1, 1};
	int* map = new int[sContour.size()];
	memset(map, -1, sContour.size()*sizeof(map));

	int cSize = sContour.size();
	for(int p=0; p < cSize; p++) {
		if(tips[p] > 0) {
			int val = 1e6;
			int flg = 0;
			int idx[2];
			for(int d=0; d < 2; d++) {
				idx[d] = p + dir[d];
				if(idx[d] < 0)
					idx[d] += cSize;
				idx[d] %= cSize;
				if(labels[idx[d]] < val && labels[idx[d]] > -1) {
					flg ++;
					val = labels[idx[d]];
				}
			}
			if(flg == 2) {
				map[std::max(labels[idx[0]], labels[idx[1]])] = std::min(labels[idx[0]], labels[idx[1]]);
			}
			if(flg > 0) {
				labels[p] = val;
			}
			else {
				num_label ++;
				labels[p] = num_label;
			}
		}
	}
	int num_fintips = 0;
	for(int c=0; c < cSize; c++) {
		if(map[labels[c]] > -1)
			labels[c] = map[labels[c]];
		if(labels[c] > num_fintips)
			num_fintips = labels[c];
	}
	num_fintips ++;

	double* cnt = new double[num_fintips];
	for(int i=0;i<num_fintips; i++)
		cnt[i] = 0;

	this->finPos.resize(num_fintips, Vector2(0, 0));
	for(unsigned int c=0; c < sContour.size(); c++) {
		if(labels[c] > -1) {
			this->finPos[labels[c]].Add(sContour[c].x, sContour[c].y);
			cnt[labels[c]] ++;
		}
	}

	for(unsigned int l=0; l < this->finPos.size(); l++) {
		if(cnt[l] != 0)
			this->finPos[l].Mult(1 / cnt[l]);
	}

/*
	cv::Mat tmp(imgMask.rows, imgMask.cols, CV_8UC1);
	tmp.setTo(0);
	for(unsigned int c=0; c < sContour.size(); c++) {
		if(labels[c] > -1) {
			tmp.at<uchar>(sContour[c].y, sContour[c].x) = std::min(255, (labels[c] + 1) * 50);
		}
		else
			tmp.at<uchar>(sContour[c].y, sContour[c].x) = 20;
	}
	cv::imshow("contour", tmp);
*/

	delete [] map;
	delete [] tips;
	delete [] labels;
	delete [] cnt;

	return this->finPos;
}

void FintipExtraction::dilate(int *contour, int size, int itr) {
	for(int t=0; t < itr; t++) {
		int* tmp = new int[size];
		memcpy(tmp, contour, size * sizeof(contour));
		for(int c=0; c < size; c++) {
			int idx[2] = {c-1, c+1};
			for(int i=0; i < 2; i++) {
				idx[i] = std::max(idx[i], -idx[i])%size;
			}
			if(tmp[c] == 1) {
				for(int i=0; i < 2; i++) {
					contour[idx[i]] = 1;
				}
			}
		}
		delete[] tmp;
	}
}

void FintipExtraction::erode(int *contour, int size, int itr) {
	for(int t=0; t < itr; t++) {
		int* tmp = new int[size];
		memcpy(tmp, contour, size * sizeof(contour));
		for(int c=0; c < size; c++) {
			int idx[2] = {c-1, c+1};
			for(int i=0; i < 2; i++) {
				idx[i] = std::max(idx[i], -idx[i])%size;
			}
			if(tmp[c] == 0) {
				for(int i=0; i < 2; i++) {
					contour[idx[i]] = 0;
				}
			}

		}
		delete[] tmp;
	}
}