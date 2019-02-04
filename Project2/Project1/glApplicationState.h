#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

#include "Vector3f.h"
#include "Vector4f.h"
#include "cyMatrix.h"
class glApplicationState
{
public:
	glApplicationState() {}
	~glApplicationState() {}
	int aButton;
	int aState;
	int ax;
	int ay;
	Vector3f currentPosition;
	Vector3f currentRotation;
	Vector3f GetCurrentPosition() { return currentPosition; }
	Vector3f GetCurrentRotation() { return currentRotation; }
	void SetCurrentPosition(Vector3f value) { currentPosition = value; }
	void SetCurrentRotation(Vector3f value) {
		currentRotation = value;
		// update UnitX & UnitZ;
		// (1,0,0)-> 4 elements quaternion
		// 4 elements quaternion -> rotation(by current Rotation)
		// get current vector
		Vector4f tmp = FromAxis(Vector3f(1, 0, 0), currentRotation.z).normalized();
		UnitX = Vector3f(tmp.x, tmp.y, tmp.z);
		tmp = FromAxis(Vector3f(0, 0, 1), currentRotation.z).normalized();
		UnitZ = Vector3f(tmp.x, tmp.y, tmp.z);
	}
	
	Vector3f instantPosition, instantRotation;
	Vector3f UnitX = Vector3f(1, 0, 0);
	Vector3f UnitZ = Vector3f(0, 0, 1);
	const float magPosition = 0.01f;
	const float magRotation = 0.1f;
	
	static Vector4f FromAxis(const Vector3f &v, float angle) {
		const float pi = 3.1415926f;
		Vector4f dst;
		float sinAngle; angle = angle * M_PI / 360;
		Vector3f vn(v);
		vn = vn.normalized();

		sinAngle = sin(angle);

		dst.x = (vn.x * sinAngle);
		dst.y = (vn.y * sinAngle);
		dst.z = (vn.z * sinAngle);
		dst.w = cos(angle);
		return dst;
	}

	static Vector4f QuaternionFromEuler(float pitch, float yaw, float roll) {
		Vector4f dst;
		
		float p = M_PI * pitch / 180.0f / 2.0f ;
		float y = M_PI * yaw / 180.0f / 2.0f;
		float r = M_PI * roll / 180.0f / 2.0f;

		float sinp = sin(p); float siny = sin(y); float sinr = sin(r); float cosp = cos(p); float cosy = cos(y); float cosr = cos(r);

		dst.x = sinr * cosp * cosy - cosr * sinp * siny;
		dst.y = cosr * sinp * cosy + sinr * cosp * siny;
		dst.z = cosr * cosp * siny - sinr * sinp * cosy;
		dst.w = cosr * cosp * cosy + sinr * sinp * siny;
		dst.normalized();
		return Vector4f(dst);
	}

	static Vector4f QuaternionMultiply(Vector4f p, Vector4f q) {
		return Vector4f(
			p.w * q.x + p.x * q.w + p.y * q.z - p.x * q.y,
			p.w * q.y - p.x * q.z + p.y * q.w + p.z * q.x,
			p.w * q.z + p.x * q.y - p.y * q.x + p.z * p.w,
			-p.x * q.x - p.y * q.y - p.z * q.z + p.w * q.w);
	}

	cyMatrix4f getRotationMatrixByQuaternion(Vector4f origin) const {
		float x2 = origin.x * origin.x;
		float y2 = origin.y * origin.y;
		float z2 = origin.z * origin.z;
		float xy = origin.x * origin.y;
		float xz = origin.x * origin.z;
		float yz = origin.y * origin.z;
		float wx = origin.w * origin.x;
		float wy = origin.w * origin.y;
		float wz = origin.w * origin.z;

		return cyMatrix4f(
			1.0f - 2.0f * (y2 + z2), 2.0f * (xy - wz), 2.0f * (xz + wy), 0.0f,
			2.0f * (xy + wz), 1.0f - 2.0f * (x2 + z2), 2.0f * (yz - wx), 0.0f,
			2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (x2 + y2), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}
};

