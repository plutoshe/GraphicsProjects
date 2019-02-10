#pragma once
#include "cmath"
#define _USE_MATH_DEFINES
#include "cyMatrix.h"
#include "math.h"
#define ToRadian(x) ((x) * M_PI / 180.0f)
#define ToDegree(x) ((x) * 180.0f / M_PI)

class PersProjInfo
{
public:
	PersProjInfo();
	~PersProjInfo();
	float FOV = 60.0f;
	float Height = 1024;
	float Width = 768;
	float zNear = 1.0f;
	float zFar = 100.0f;
	float yLower, yUpper, xLower, xUpper;
	void init() {
		/*yLower = tan*/
	}

	/*float ToRadian(float degree) {
		return (degree * M_PI) / 180;
	}*/

	void InitPerspectiveProj(cyMatrix4f& m) 
	{
		const float ar = Width / Height;
		const float zNear = zNear;
		const float zFar = zFar;
		const float zRange = zNear - zFar;
		const float tanHalfFOV = tanf(ToRadian(FOV / 2.0));

		/*m.m[0][0] = 1.0f / (tanHalfFOV * ar);
		m.m[0][1] = 0.0f;
		m.m[0][2] = 0.0f;
		m.m[0][3] = 0.0f;

		m.m[1][0] = 0.0f;
		m.m[1][1] = 1.0f / tanHalfFOV;
		m.m[1][2] = 0.0f;
		m.m[1][3] = 0.0f;

		m.m[2][0] = 0.0f;
		m.m[2][1] = 0.0f;
		m.m[2][2] = (-zNear - zFar) / zRange;
		m.m[2][3] = 2.0f * zFar * zNear / zRange;

		m.m[3][0] = 0.0f;
		m.m[3][1] = 0.0f;
		m.m[3][2] = 1.0f;
		m.m[3][3] = 0.0f;*/
	}
};

