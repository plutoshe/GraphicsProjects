#include "Vector4f.h"

Vector4f::Vector4f() {}

Vector4f::Vector4f(float px, float py, float pz, float pw) : x(px), y(py), z(pz), w(pw) {}

Vector4f::~Vector4f() {}

Vector4f Vector4f::operator+(const Vector4f& addend) {
	return Vector4f(x + addend.x, y + addend.y, z + addend.z, w + addend.w);
}

Vector4f Vector4f::operator-(const Vector4f& minus) {
	return Vector4f(x - minus.x, y - minus.y, z - minus.z, w - minus.w);
}

//Vector4f Vector4f::operator*(float mul) {
//	return Vector4f(x * mul, y * mul, z * mul, w * mul);
//}

Vector4f Vector4f::operator/(float div) {
	return Vector4f(x / div, y / div, z / div, w / div);
}


bool Vector4f::operator==(const Vector4f& comp) const {
	return (x == comp.x) && (y == comp.y) && (z == comp.z) && (w == comp.w);
}

void Vector4f::operator=(const Vector4f& origin) {
	x = origin.x;
	y = origin.y;
	z = origin.z;
	w = origin.w;
}

Vector4f Vector4f::normalized() {
	float len = this->length();
	if (len > 0)
		return Vector4f(x / len, y / len, z / len, w / len);
	return Vector4f(0, 0, 0, 0);
}

float Vector4f::length() {
	return sqrt((x * x) + (y * y) + (z * z) + (w * w));
}

void Vector4f::zero() {
	x = y = z = w = 0;
}

