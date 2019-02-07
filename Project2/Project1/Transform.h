#pragma once
#include "cyMatrix.h"
class Transform
{
public:
	Transform();
	~Transform();

	static cyMatrix4f InitTranslationTransform(float offset_x, float offset_y, float offset_z) {
		return cyMatrix4f(
			1.f, 0.f, 0.f, offset_x,
			0.f, 1.f, 0.f, offset_y,
			0.f, 0.f, 1.f, offset_z,
			0.f, 0.f, 0.f, 1.f);
		/*return cyMatrix4f(
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			offset_x, offset_y, offset_z, 1.f);*/
	}
};

