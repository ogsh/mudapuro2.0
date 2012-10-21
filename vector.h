#ifndef __VECTOR__
#define __VECTOR__

using namespace System;

public class Vector2 {
public:
	double x;
	double y;
	Vector2() {
		this->x = 0.0;
		this->y = 0.0;
	}
	Vector2(double x, double y) {
		this->x = x;
		this->y = y;
	}
	~Vector2(){}
	void Set(double x, double y) {
		this->x = x;
		this->y = y;
	}
	void Set(Vector2& v) {
		this->x = v.x;
		this->y = v.y;
	}
	void Add(double x, double y) {
		this->x += x;
		this->y += y;
	}
	void Add(Vector2& v) {
		this->x += v.x;
		this->y += v.y;
	}
	void Mult(double c) {
		this->x *= c;
		this->y *= c;
	}
	void Rot(double t) {
		double tmpx = this->x;
		double tmpy = this->y;
		this->x = tmpx * Math::Cos(t) - tmpy * Math::Sin(t);
		this->y = tmpx * Math::Sin(t) + tmpy * Math::Cos(t);
	}
	double Length() {
		return Math::Sqrt(this->x*this->x + this->y*this->y);
	}
	double Slength() {
		return this->x*this->x + this->y*this->y;
	}
	double Distance(Vector2& v) {
		return Math::Sqrt((this->x - v.x)*(this->x - v.x) + (this->y - v.y)*(this->y - v.y));
	}
	double Distance(double x, double y) {
		return Math::Sqrt((this->x - x)*(this->x - x) + (this->y - y)*(this->y - y));
	}
	double Sdistance(Vector2& v) {
		return (this->x - v.x)*(this->x - v.x) + (this->y - v.y)*(this->y - v.y);
	}
	double Sdistance(double x, double y) {
		return (this->x - x)*(this->x - x) + (this->y - y)*(this->y - y);
	}
	double Product(double x, double y) {
		return this->x*x + this->y*y;
	}
	double Product(Vector2& v) {
		return this->Product(v.x, v.y);
	}
	double OuterProduct(double x, double y) {
		return this->x * y - this->y * x;
	}
	double OuterProduct(Vector2& v) {
		return this->x * v.y - this->y * v.x;
	}
};


public class Vector3 {
public:
	double x;
	double y;
	double z;

	Vector3() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	Vector3(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	
	Vector3(const Vector3& v3) {
		this->x = v3.x;
		this->y = v3.y;
		this->z = v3.z;
	}

	~Vector3() {
	}

	void Set(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void Set(Vector3& v) {
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	}

	void Add(double x, double y, double z) {
		this->x += x;
		this->y += y;
		this->z += z;
	}

	void Add(Vector3& v3) {
		this->x += v3.x;
		this->y += v3.y;
		this->z += v3.z;
	}

	void Sub(double x, double y, double z) {
		this->x -= x;
		this->y -= y;
		this->z -= z;
	}

	void Sub(Vector3& v3) {
		this->x -= v3.x;
		this->y -= v3.y;
		this->z -= v3.z;
	}

	void Mult(double c) {
		this->x *= c;
		this->y *= c;
		this->z *= c;
	}

	double Length() {
		return sqrt(x*x + y*y + z*z);
	}

	double Slength() {
		return x*x + y*y + z*z;
	}

	double Product(double x, double y, double z) {
		return this->x * x + this->y * y + this->z * z;
	}

	double Product(Vector3& v3) {
		return this->x * v3.x + this->y * v3.y + this->z * v3.z;
	}

	Vector3* OuterProduct(Vector3& v3) {
		return this->OuterProduct(v3.x, v3.y, v3.z);
	}

	Vector3* OuterProduct(double x, double y, double z) {
		return  new Vector3(this->y*z - this->z*y, this->z*x - this->x*z, this->x*y - this->y*x);
	}

	Vector3* UnitVector() {
		if(this->Length() <= 0)
			return new Vector3(0, 0, 0);
		else
			return new Vector3(this->x / this->Length(), this->y / this->Length(), this->z / this->Length());
	}
};

#endif