#pragma once
#include <iostream>
class Vector3f
{

public:
	Vector3f();
	Vector3f(float px, float py, float pz);
	~Vector3f();
	inline friend std::ostream& operator<<(std::ostream& os, const Vector3f p) {
		os << "(" << p.x << "," << p.y << "," << p.z << ")";
		return os;
	}
	Vector3f operator+(const Vector3f& addend);
	Vector3f operator-(const Vector3f& minus);
	Vector3f operator*(const float mul);
	Vector3f operator/(const float div);
	bool operator==(const Vector3f& comp) const;
	void operator=(const Vector3f& origin);
	
	float x, y, z;
	Vector3f normalized();
	float length();
	void clear();
	
};

