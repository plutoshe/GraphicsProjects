//#pragma once
//#ifdef GLEW_STATIC
//#define GLEWAPI extern
//#else
//#ifdef GLEW_BUILD
//#define GLEWAPI extern __declspec(dllexport)
//#else
//#define GLEWAPI extern __declspec(dllimport)
//#endif
//#endif
//#include<GL/glew.h>
//#include<GL/freeglut.h>
//#include<iostream>
//#include "Vector3f.h"
//#include "cyTriMesh.h"
//#include "Log.h"
//#include "cyPoint.h"
//#include <fstream>
//using namespace std;
//
//class glApplication
//{
//public:
//	glApplication();
//	~glApplication();
//	void Init();
//	void Compile();
//	void Run();
//
//	void Render();
//	void CreateVertexBuffer();
//
//	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
//	void CompileShaders();
//	void idleFunc();
//	void processNormalKeys(unsigned char key, int x, int y);
//
//	void processMovement(int x, int y);
//	void changeViewport(int w, int h);
//	void loadVertex(cyTriMesh &trimesh, char* filename);
//
//	void file_reader(string file, string &result);
//	void processMouse(int button, int state, int x, int y);
//
//	cyTriMesh meshData;
//	char* pVSFileName;
//	char* pFSFileName = "shader.fs";
//	char* meshFile;
//
//	int argc;
//	char** argv;
//
//	GLuint VBO;
//	int aButton;
//	int aState;
//	int ax;
//	int ay;
//
//};
//
