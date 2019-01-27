#include "Vector3f.h"

Vector3f::Vector3f() {}

Vector3f::Vector3f(float px, float py, float pz) : x(px), y(py), z(pz) {}

Vector3f::~Vector3f() {}

Vector3f Vector3f::operator+(const Vector3f& addend) {
	return Vector3f(x + addend.x, y + addend.y, z + addend.z);
}

Vector3f Vector3f::operator-(const Vector3f& minus) {
	return Vector3f(x - minus.x, y - minus.y, z - minus.z);
}

Vector3f Vector3f::operator*(float mul) {
	return Vector3f(x * mul, y * mul, z * mul);
}

Vector3f Vector3f::operator/(float div) {
	return Vector3f(x / div, y / div, z / div);
}


bool Vector3f::operator==(const Vector3f& comp) const {
	return (x == comp.x) && (y == comp.y) && (z == comp.z);
}

void Vector3f::operator=(const Vector3f& origin) {
	x = origin.x;
	y = origin.y;
	z = origin.z;
}

Vector3f Vector3f::normalized() {
	float len = this->length();
	if (len > 0)
		return Vector3f(x / len, y / len, z / len);
	return Vector3f(0, 0, 0);
}

float Vector3f::length() {
	return sqrt((x * x) + (y * y) + (z * z));
}

void Vector3f::clear() {
	x = y = z = 0;
}

