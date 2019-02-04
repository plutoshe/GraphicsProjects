//#pragma once
//#include "Vector3f.h"
//
//namespace Quaternion {
//	void FromAxis(const Vector3f &v, float angle) {
//		float sinAngle; angle *= 0.5f;
//		Vector3f vn(v);
//		vn = vn.normalized;
//
//		sinAngle = sin(angle);
//
//		x = (vn.x * sinAngle);
//		y = (vn.y * sinAngle);
//		z = (vn.z * sinAngle);
//		w = cos(angle);
//	}
//
//	void Quaternion::FromEuler(float pitch, float yaw, float roll) {
//		float p = pitch * PIOVER180 / 2.0;
//		float y = yaw * PIOVER180 / 2.0;
//		float r = roll * PIOVER180 / 2.0;
//
//		float sinp = sin(p); float siny = sin(y); float sinr = sin(r); float cosp = cos(p); float cosy = cos(y); float cosr = cos(r);
//
//		x = sinr * cosp * cosy - cosr * sinp * siny;
//		y = cosr * sinp * cosy + sinr * cosp * siny;
//		z = cosr * cosp * siny - sinr * sinp * cosy;
//		w = cosr * cosp * cosy + sinr * sinp * siny;
//
//		normalise();
//	}
//
//	Matrix4 Quaternion::getMatrix() const {
//		float x2 = x * x;
//		float y2 = y * y;
//		float z2 = z * z;
//		float xy = x * y;
//		float xz = x * z;
//		float yz = y * z;
//		float wx = w * x;
//		float wy = w * y;
//		float wz = w * z;
//
//		// This calculation would be a lot more complicated for non-unit length quaternions
//		// Note: The constructor of Matrix4 expects the Matrix in column-major format like expected by
//		// OpenGL
//		return Matrix4(
//			1.0f - 2.0f * (y2 + z2), 2.0f * (xy - wz), 2.0f * (xz + wy), 0.0f, 2.0f * (xy + wz),
//			1.0f - 2.0f * (x2 + z2), 2.0f * (yz - wx), 0.0f, 2.0f * (xz - wy),
//			2.0f * (yz + wx), 1.0f - 2.0f * (x2 + y2), 0.0f,
//			0.0f, 0.0f, 0.0f, 1.0f)
//	}
//
//	void Quaternion::getAxisAngle(Vector3 *axis, float *angle) {
//		float scale = sqrt(x * x + y * y + z * z);
//		axis->x = x / scale;
//		axis->y = y / scale;
//		axis->z = z / scale;
//		*angle = acos(w) * 2.0f;
//	}
//}
//
//
//void Camera::movex(float xmmod) { pos += rotation * Vector3(xmmod, 0.0f, 0.0f); }
//
//void Camera::movey(float ymmod) { pos.y -= ymmod; }
//
//void Camera::movez(float zmmod) { pos += rotation * Vector3(0.0f, 0.0f, -zmmod); }
//
//void Camera::rotatex(float xrmod) { Quaternion nrot(Vector3(1.0f, 0.0f, 0.0f), xrmod * PIOVER180); rotation = rotation * nrot; }
//
//void Camera::rotatey(float yrmod) { Quaternion nrot(Vector3(0.0f, 1.0f, 0.0f), yrmod * PIOVER180); rotation = nrot * rotation; }
//
//void Camera::tick(float seconds) {
//	if (xrot != 0.0f) rotatex(xrot * seconds * rotspeed); if (yrot != 0.0f) rotatey(yrot * seconds * rotspeed);
//
//	if (xmov != 0.0f) movex(xmov * seconds * movespeed); if (ymov != 0.0f) movey(ymov * seconds * movespeed); if (zmov != 0.0f) movez(zmov * seconds * movespeed);
//}