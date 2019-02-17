#pragma once
#include "util.h"
#include "Vector3f.h"
#include "cyMatrix.h"
struct DirectionLight
{
	Vector3f Color;
	float AmbientIntensity;
};

class lightUtil : public util
{
public:

	lightUtil();
	~lightUtil();
	virtual bool Init();

	void SetWVP(const cyMatrix4f* WVP);
	void SetTextureUnit(unsigned int TextureUnit);
	void SetDirectionalLight(const DirectionLight& Light);

private:
	GLuint m_WVPLocation;
	GLuint m_samplerLocation;
	GLuint m_dirLightColorLocation;
	GLuint m_dirLightAmbientIntensityLocation;
};