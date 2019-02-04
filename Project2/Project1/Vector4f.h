#pragma once
#include <iostream>
class Vector4f
{

public:
	Vector4f();
	Vector4f(float px, float py, float pz, float pw);
	~Vector4f();
	inline friend std::ostream& operator<<(std::ostream& os, const Vector4f p) {
		os << "(" << p.x << "," << p.y << "," << p.z << "," << p.w <<  ")";
		return os;
	}
	Vector4f operator+(const Vector4f& addend);
	Vector4f operator-(const Vector4f& minus);
	//Vector4f operator*(const float mul);
	friend Vector4f operator *(const Vector4f& multiply, const float mul) {
		return Vector4f(multiply.x * mul, multiply.y * mul, multiply.z * mul, multiply.w * mul);
	}
	friend Vector4f operator *(const float mul, const Vector4f& multiply) {
		return multiply * mul;
	}
	Vector4f operator/(const float div);
	bool operator==(const Vector4f& comp) const;
	void operator=(const Vector4f& origin);

	float x, y, z, w;
	Vector4f normalized();
	float length();
	void zero();
};

