#pragma once
#include "Vector3f.h"
#include "cyMatrix.h"
class Camera
{
public:
	Camera() {}
	Camera(const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up):
		m_pos(Pos), m_target(Target), m_up(Up) {}

	void SetCamera(const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up) {
		m_pos = Pos;
		m_target = Target;
		m_up = Up;
	}

	bool OnKeyboard(int Key);
	const Vector3f& GetPos() { return m_pos; }
	const Vector3f& GetTarget() { return m_target; };
	const Vector3f& GetUp() { return m_up; }
	const float StepSize = 0.1f;
	cyMatrix4f m;
	cyMatrix4f InitCameraTransform(const Vector3f& Target, const Vector3f& Up)
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
	}

	cyMatrix4f InitialMyCameraTransform() {
		m = InitCameraTransform(m_target, m_up);
		return m;
	}

private:
	Vector3f m_pos;
	Vector3f m_target;
	Vector3f m_up;
};