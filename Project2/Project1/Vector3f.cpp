#include "Vector3f.h"

Quaternion::Quaternion(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

void Quaternion::Normalize()
{
	float Length = sqrtf(x * x + y * y + z * z + w * w);

	x /= Length;
	y /= Length;
	z /= Length;
	w /= Length;
}


Quaternion Quaternion::Conjugate()
{
	Quaternion ret(-x, -y, -z, w);
	return ret;
}

Quaternion operator*(const Quaternion& l, const Quaternion& r)
{
	const float w = (l.w * r.w) - (l.x * r.x) - (l.y * r.y) - (l.z * r.z);
	const float x = (l.x * r.w) + (l.w * r.x) + (l.y * r.z) - (l.z * r.y);
	const float y = (l.y * r.w) + (l.w * r.y) + (l.z * r.x) - (l.x * r.z);
	const float z = (l.z * r.w) + (l.w * r.z) + (l.x * r.y) - (l.y * r.x);

	Quaternion ret(x, y, z, w);

	return ret;
}

Quaternion operator*(const Quaternion& q, const Vector3f& v)
{
	float w = -(q.x * v.x) - (q.y * v.y) - (q.z * v.z);
	float x = (q.w * v.x) + (q.y * v.z) - (q.z * v.y);
	float y = (q.w * v.y) + (q.z * v.x) - (q.x * v.z);
	float z = (q.w * v.z) + (q.x * v.y) - (q.y * v.x);

	Quaternion ret(x, y, z, w);

	return ret;
}

Vector3f::Vector3f() {}

Vector3f::Vector3f(float px, float py, float pz) : x(px), y(py), z(pz) {}

Vector3f::~Vector3f() {}

Vector3f Vector3f::operator+(const Vector3f& addend) {
	return Vector3f(x + addend.x, y + addend.y, z + addend.z);
}

Vector3f Vector3f::operator-(const Vector3f& minus) {
	return Vector3f(x - minus.x, y - minus.y, z - minus.z);
}
//
//Vector3f Vector3f::operator*(float mul) {
//	return Vector3f(x * mul, y * mul, z * mul);
//}

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

void Vector3f::zero() {
	x = y = z = 0;
}

void Vector3f::Rotate(float Angle, const Vector3f& Axe)
{
	const float SinHalfAngle = sinf(ToRadian(Angle / 2));
	const float CosHalfAngle = cosf(ToRadian(Angle / 2));

	const float Rx = Axe.x * SinHalfAngle;
	const float Ry = Axe.y * SinHalfAngle;
	const float Rz = Axe.z * SinHalfAngle;
	const float Rw = CosHalfAngle;
	Quaternion RotationQ(Rx, Ry, Rz, Rw);

	Quaternion ConjugateQ = RotationQ.Conjugate();
	//  ConjugateQ.Normalize();
	Quaternion W = RotationQ * (*this) * ConjugateQ;

	x = W.x;
	y = W.y;
	z = W.z;
}