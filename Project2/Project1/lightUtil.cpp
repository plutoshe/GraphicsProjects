#include "lightUtil.h"



lightUtil::lightUtil()
{
}


lightUtil::~lightUtil()
{
}

static const char* pVS = "                                                          \n\
#version 330                                                                        \n\
                                                                                    \n\
layout (location = 0) in vec3 Position;                                             \n\
layout (location = 1) in vec2 TexCoord;                                             \n\
                                                                                    \n\
uniform mat4 gWVP;                                                                  \n\
                                                                                    \n\
out vec2 TexCoord0;                                                                 \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    gl_Position = gWVP * vec4(Position, 1.0);                                       \n\
    TexCoord0 = TexCoord;                                                           \n\
}";

static const char* pFS = "                                                          \n\
#version 330                                                                        \n\
                                                                                    \n\
in vec2 TexCoord0;                                                                  \n\
 uniform sampler2D gSampler;                                                                                     \n\
out vec4 FragColor;                                                                 \n\
                                                                                    \n\
struct DirectionalLight                                                             \n\
{                                                                                   \n\
    vec3 Color;                                                                     \n\
    float AmbientIntensity;                                                         \n\
};                                                                                  \n\
                                                                                    \n\
uniform DirectionalLight gDirectionalLight;                                         \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    FragColor = texture2D(gSampler, TexCoord0.xy) *  vec4(gDirectionalLight.Color, 1.0f) *                               \n\
                gDirectionalLight.AmbientIntensity;                                 \n\
}";
//uniform sampler2D gSampler;                                                         \n\
//texture2D(gSampler, TexCoord0.xy) *    vec4(0.5,0.5,0.5,1) *                             \n\

bool lightUtil::Init()
{
	if (!util::Init())
	{
		return false;
	}

	if (!AddShader(GL_VERTEX_SHADER, pVS))
	{
		return false;
	}

	if (!AddShader(GL_FRAGMENT_SHADER, pFS))
	{
		return false;
	}

	if (!Finalize())
	{
		return false;
	}

	m_WVPLocation = GetUniformLocation("gWVP");
	m_samplerLocation = GetUniformLocation("gSampler");
	m_dirLightColorLocation = GetUniformLocation("gDirectionalLight.Color");
	m_dirLightAmbientIntensityLocation = GetUniformLocation("gDirectionalLight.AmbientIntensity");

	if (m_dirLightAmbientIntensityLocation == 0xFFFFFFFF ||
		m_WVPLocation == 0xFFFFFFFF ||
		m_samplerLocation == 0xFFFFFFFF ||
		m_dirLightColorLocation == 0xFFFFFFFF)
	{
		return false;
	}

	return true;
}

void lightUtil::SetWVP(const cyMatrix4f* WVP)
{
	glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP->data);
}


void lightUtil::SetTextureUnit(unsigned int TextureUnit)
{
	glUniform1i(m_samplerLocation, TextureUnit);
}


void lightUtil::SetDirectionalLight(const DirectionLight& Light)
{
	glUniform3f(m_dirLightColorLocation, Light.Color.x, Light.Color.y, Light.Color.z);
	glUniform1f(m_dirLightAmbientIntensityLocation, Light.AmbientIntensity);
}