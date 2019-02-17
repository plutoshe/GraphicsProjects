﻿#ifdef GLEW_STATIC
	#define GLEWAPI extern
#else
	#ifdef GLEW_BUILD
		#define GLEWAPI extern __declspec(dllexport)
	#else
		#define GLEWAPI extern __declspec(dllimport)
	#endif
#endif
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <fstream>
#include <cstdio> 

#include <math.h>
#include<GL/glew.h>
#include<GL/freeglut.h>
#include <assert.h>

#include "cyTriMesh.h"
#include "cyPoint.h"
#include "Log.h"
#include "Vector3f.h"
#include "glApplicationState.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "pipeline.h"
#include <string.h>
#include "PersProjInfo.h"

// 屏幕宽高宏定义
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

using namespace std;
#ifdef GLEW_STATIC
#define GLEWAPI extern
#else
#ifdef GLEW_BUILD
#define GLEWAPI extern __declspec(dllexport)
#else
#define GLEWAPI extern __declspec(dllimport)
#endif
#endif
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <fstream>
#include <cstdio> 

#include <math.h>
#include<GL/glew.h>
#include<GL/freeglut.h>
#include <assert.h>

#include "cyTriMesh.h"
#include "cyPoint.h"
#include "Log.h"
#include "Vector3f.h"
#include "glApplicationState.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "pipeline.h"
#include <string.h>
#include "PersProjInfo.h"
#include "Camera.h"
#include "Transform.h"
#include "glutBackend.h"
// 屏幕宽高宏定义
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

class GraphicsApplication: virtual public ICallbacks {
public:
	GLuint VBO;
	GLuint IBO;
	GLuint gWorldLocation;
	// 透视变换配置参数数据结构
	PersProjInfo gPersProjInfo;
	Camera *pCamera;
	const char* pVSFileName = "shader.vs";
	const char* pFSFileName = "shader.fs";
	cyTriMesh meshdata;
	GraphicsApplication() {}
	bool InitMode(int argc, char** argv) {
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
		return false;
	}

	bool InitWindow() {
		glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
		glutInitWindowPosition(100, 100);
		glutCreateWindow("Camera");

		GLenum res = glewInit();
		if (res != GLEW_OK) {
			fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
			return 1;
		}
		return false;
	}

	bool Prepare() {
		loadMesh(meshdata, "");
		pCamera = new Camera();
		Vector3f CameraPos1(0.f, 75.f, 0.f);
		Vector3f CameraTarget1(0.f, -1.f, 0.f);
		Vector3f CameraUp1(0.0f, 0.f, 1.0f);

		pCamera->SetCamera(CameraPos1, CameraTarget1, CameraUp1);
		// Must be done after glut is initialized!

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		CreateVertexBuffer();
		CreateIndexBuffer();

		CompileShaders();

		// 初始化透视变换配置参数
		gPersProjInfo.FOV = 30.0f;
		gPersProjInfo.Height = WINDOW_HEIGHT;
		gPersProjInfo.Width = WINDOW_WIDTH;
		gPersProjInfo.zNear = 1.0f;
		gPersProjInfo.zFar = 100.0f;
		return false;
	}

	void Run() {
		GLUTBackendRun(this);
	}

	void file_reader(string file, string &result)
	{
		string line;
		std::ifstream myfile(file);
		if (myfile.is_open())
		{
			while (myfile.good())
			{
				getline(myfile, line);
				result += line + "\n";
			}
			myfile.close();
		}
		else
		{
			cout << "Unable to open file";
		}
	}

	void CompileShaders()
	{
		GLuint ShaderProgram = glCreateProgram();

		if (ShaderProgram == 0) {
			fprintf(stderr, "Error creating shader program\n");
			exit(1);
		}

		std::string vs, fs;


		file_reader(pVSFileName, vs);
		file_reader(pFSFileName, fs);
		AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
		AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

		GLint Success = 0;
		GLchar ErrorLog[1024] = { 0 };

		glLinkProgram(ShaderProgram);
		glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
		if (Success == 0) {
			glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
			fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
			exit(1);
		}

		glValidateProgram(ShaderProgram);
		glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
		if (!Success) {
			glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
			fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
			exit(1);
		}

		glUseProgram(ShaderProgram);

		gWorldLocation = glGetUniformLocation(ShaderProgram, "gWorld");
		//assert(gWorldLocation != 0xFFFFFFFF);
	}

	void loadMesh(cyTriMesh &trimesh, const char* filename) {
		trimesh.LoadFromFileObj("teapot.obj");
	}
	void CreateVertexBuffer()
	{
		Vector3f* Vertices = new Vector3f[meshdata.NV()];
		for (int i = 0; i < meshdata.NV(); i++) {
			Vertices[i] = Vector3f(
				meshdata.V(i).x,
				meshdata.V(i).y,
				meshdata.V(i).z);
		}
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3f) * meshdata.NV(), Vertices, GL_STATIC_DRAW);
	}

	void CreateIndexBuffer()
	{
		unsigned int *Indices = new unsigned int[3 * meshdata.NF()];
		for (int i = 0; i < meshdata.NF(); i++) {


			auto face = meshdata.F(i);
			for (int k = 0; k < 3; k++) {
				Indices[i * 3 + k] = face.v[k];
			}

		}

		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 3 * meshdata.NF(), Indices, GL_STATIC_DRAW);
	}

	static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
	{
		GLuint ShaderObj = glCreateShader(ShaderType);
		if (ShaderObj == 0) {
			fprintf(stderr, "Error creating shader type %d\n", ShaderType);
			exit(1);
		}
		const GLchar* p[1];
		p[0] = pShaderText;
		GLint Lengths[1];
		Lengths[0] = strlen(pShaderText);
		glShaderSource(ShaderObj, 1, p, Lengths);
		glCompileShader(ShaderObj);
		GLint success;
		glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
		if (!success) {
			GLchar InfoLog[1024];
			glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
			fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
			exit(1);
		}

		glAttachShader(ShaderProgram, ShaderObj);
	}


	void RenderSceneCB()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		static float Scale = 0.0f;

		Scale += 0.1f;

		//Pipeline p;
		//p.Rotate(0.0f, Scale, 0.0f);
		//p.WorldPos(0.0f, 0.0f, 5.0f);
		//// 设置投影变换的参数
		//p.SetPerspectiveProj(gPersProjInfo);
		float xLowBound = -1.f;
		float xUpperBound = 1.f;
		float yLowBound = -1.f;
		float yUpperBound = 1.f;
		float zLowBound = 1.f;
		float zUpperBound = 100.f;
		cyMatrix4f aMat4(
			2 * zLowBound / (xUpperBound - xLowBound), 0.0, 0.0, 0.0,
			0.0, 2 * zLowBound / (yUpperBound - yLowBound), 0.0, 0.0,

			0.0, 0.0, (-zLowBound - zUpperBound) / (-zUpperBound + zLowBound), 2 * zLowBound * zUpperBound / (-zUpperBound + zLowBound),
			0.0, 0.0, 1.0, 0.f);
		aMat4.Transpose();
		cyMatrix4f bMat4(
			1.299f, 0.0f, 0.f, 0.f,
			0.0f, 1.732f, 0.f, 0.f,
			0.0f, 0.0f, 1.02f, -2.02f,
			0.0f, 0.0f, 1.f, 0);
		//bMat4.Transpose();
		aMat4 =
			bMat4 *
			pCamera->InitialMyCameraTransform() *
			Transform::InitTranslationTransform(-pCamera->GetPos().x, -pCamera->GetPos().y, -pCamera->GetPos().z);
		//Transform::InitTranslationTransform(0,0,3);
		aMat4.Transpose();

		glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, (const GLfloat*)aMat4.data);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

		glDrawElements(GL_TRIANGLES, meshdata.NF() * 4, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);

		glutSwapBuffers();
	}

	void OnKeyboard(unsigned char Key, int x, int y)
	{
		pCamera->OnKeyboard(Key);
	}

	void PassiveMouseCB(int x, int y)
	{
		//printf("PassiveMouseCB: %d %d\n", x, y);
	}

	void PassiveMouseDuringAction(int x, int y)
	{
		//printf("PassiveMouseAfterAction: %d %d\n", x, y);
	}

	void MouseAction(int button, int state, int x, int y) {
		printf("MouseOperation: %d %d %d %d\n", button, state, x, y);
	}
	void SpecialKeyboardCB(int Key, int x, int y) {}

	void IdleCB() { RenderSceneCB(); }
	
};

int main(int argc, char** argv)
{
	GraphicsApplication *application = new GraphicsApplication();
	if (application->InitMode(argc, argv)) {

	}
	if (application->InitWindow()) {

	}
	if (application->Prepare()) {
	}

	application->Run();
	
	return 0;
}