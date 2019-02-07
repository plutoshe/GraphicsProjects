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
//	Vector3f operator*(const float mul);
	friend Vector3f operator *(const Vector3f& multiply, const float mul) {
		return Vector3f(multiply.x * mul, multiply.y * mul, multiply.z * mul);
	}
	friend Vector3f operator *(const float mul, const Vector3f& multiply) {
		return multiply * mul;
	}
	Vector3f operator/(const float div);
	bool operator==(const Vector3f& comp) const;
	void operator=(const Vector3f& origin);
	Vector3f Cross(const Vector3f& v) const
	{
		const float _x = y * v.z - z * v.y;
		const float _y = z * v.x - x * v.z;
		const float _z = x * v.y - y * v.x;

		return Vector3f(_x, _y, _z);
	}

	float x, y, z;
	Vector3f normalized();
	Vector3f& Normalize()
	{
		const float Length = sqrtf(x * x + y * y + z * z);

		x /= Length;
		y /= Length;
		z /= Length;

		return *this;
	}

	/*cyMatrix4f InitCameraTransform(const Vector3f& Target, const Vector3f& Up)
	{
		Vector3f N = Target;
		N.Normalize();
		Vector3f U = Up;
		U.Normalize();
		U = U.Cross(Target);
		Vector3f V = N.Cross(U);
		return cyMatrix4f(
			U.x, U.y, U.z, 0.f,
			V.x, V.y, V.z, 0.f,
			N.x, N.y, N.z, 0.f,
			0.f, 0.f, 0.f, 1.f);
	}*/
	float length();
	void zero();
};

