#include "hand.h"

Hand::Hand(int imgWidth, int imgHeight) :
imgWidth(imgWidth), imgHeight(imgHeight) {
	this->he = new HE_color(imgWidth, imgHeight);
	this->fe = new FintipExtraction();

	this->Initialize();
}

Hand::~Hand() {
	if(this->he) {
		delete this->he;
		this->he = NULL;
	}
	if(this->fe) {
		delete this->fe;
		this->fe = NULL;
	}
	this->fingers.clear();
}

void Hand::Initialize() {
	this->fingers = std::vector<Finger>(this->MAX_NUM_FINGERS);
}

void Hand::Get(cv::Mat &img, cv::Mat_<unsigned short>& depth) {
	this->he->Extract(img, depth);
	std::vector<Vector2> finPos = this->fe->Get(this->he->ImgMask());
	this->num_fingers = finPos.size();
	this->fingers.resize(this->num_fingers, Finger(Vector2(0, 0)));
	for(int f=0; f < this->num_fingers; f++) {
		this->fingers[f].pos.Set(finPos[f]);
	}	

}

cv::Mat& Hand::DrawStatus(cv::Mat& img) {
	for(unsigned int f=0; f < this->fingers.size(); f++) {
		Vector2 pos = this->fingers[f].pos;
		cv::circle(img, cv::Point(pos.x, pos.y), 3, cv::Scalar(0, 0, 255), -1);
	}
	return img;
}