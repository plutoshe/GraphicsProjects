#pragma once
#include <GL/glew.h>
#include <list>
class util
{
public:
	util();
	~util();
	virtual bool Init();

	void Enable();

protected:

	bool AddShader(GLenum ShaderType, const char* pShaderText);

	bool Finalize();

	GLint GetUniformLocation(const char* pUniformName);

private:

	GLuint m_shaderProg;

	typedef std::list<GLuint> ShaderObjList;
	ShaderObjList m_shaderObjList;
};
