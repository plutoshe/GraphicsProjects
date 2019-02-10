#pragma once
#define _USE_MATH_DEFINES
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
	const float StepSize = 0.5f;
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

	void Update() {
		const Vector3f Vaxis(0.0f, 1.0f, 0.0f);
		Vector3f View(0.0f, 0.0f, 1.0f);
		View.Rotate(deflectionXZDegree, Vaxis);
		View.Normalize();

		// Rotate the view vector by the vertical angle around the horizontal axis
		Vector3f Haxis = Vaxis.Cross(View);
		Haxis.Normalize();
		View.Rotate(deflectionYZDegree, Haxis);

		m_target = View;
		m_target.Normalize();

		m_up = m_target.Cross(Haxis);
		m_up.Normalize();

		//Vector3f Vaxis(m_up);
		///*Vaxis = Vaxis.Cross(m_up);
		//Vaxis.Normalize();*/

		//Vector3f View(m_target);

		//View.Rotate(deflectionXZDegree, Vaxis);
		//View.Normalize();

		//// Rotate the view vector by the vertical angle around the horizontal axis
		//Vector3f Haxis = Vaxis.Cross(View);
		//Haxis.Normalize();
		//View.Rotate(deflectionYZDegree, Haxis);

		//m_target = View;
		//m_target.Normalize();

		//m_up = m_target.Cross(Haxis);
		//m_up.Normalize();
		//deflectionXZDegree = 0;
		//deflectionYZDegree = 0;
		//printf("target: %.2f %.2f %.2f\n", m_target.x, m_target.y, m_target.z);
		//printf("up: %.2f %.2f %.2f\n", m_up.x, m_up.y, m_up.z);
	}

private:
	Vector3f m_pos;
	Vector3f m_target;
	Vector3f m_up;

	float deflectionXZDegree = 0;
	float deflectionYZDegree = 0;
};
