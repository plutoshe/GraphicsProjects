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
#include "lightUtil.h"
#include "lodepng.h"
// 屏幕宽高宏定义
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
struct Vertex
{
	Vector3f m_pos;
	cyPoint2f m_tex;

	Vertex() {}

	Vertex(Vector3f pos, cyPoint2f tex)
	{
		m_pos = pos;
		m_tex = tex;
	}
};
class GraphicsApplication:  public ICallbacks {
public:
	GLuint VBO;
	GLuint IBO;
	GLuint gWorldLocation;
	PersProjInfo gPersProjInfo;
	const char* pVSFileName = "shader.vs";
	const char* pFSFileName = "shader.fs";
	cyTriMesh meshdata;
	Camera *pCamera;
	lightUtil* m_pEffect;
	DirectionLight m_directionalLight;
	std::vector<unsigned char> image;
	unsigned width, height;

	void loadImg() {

		unsigned error = lodepng::decode(image, width, height, "brick-specular.png");

		if (error != 0) {
			std::cout << "error " << error << ": " << lodepng_error_text(error) << std::endl;
			return;
		}
		size_t u2 = 1; while (u2 < width) u2 *= 2;
		size_t v2 = 1; while (v2 < height) v2 *= 2;
		std::vector<unsigned char> image2(u2 * v2 * 4);
		for (size_t y = 0; y < height; y++)
			for (size_t x = 0; x < width; x++)
				for (size_t c = 0; c < 4; c++) {
					image2[4 * u2 * y + 4 * x + c] = image[4 * width * y + 4 * x + c];
				}
	}
	void BindTexture() {

		GLuint texture;
		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);  //128x256 is the POT size of image that i used in this exam

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//GL_NEAREST
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);//GL_NEAREST
		glGenerateMipmap(GL_TEXTURE_2D);

	}
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
		// 初始化透视变换配置参数
		gPersProjInfo.FOV = 30.0f;
		gPersProjInfo.Height = WINDOW_HEIGHT;
		gPersProjInfo.Width = WINDOW_WIDTH;
		gPersProjInfo.zNear = 1.0f;
		gPersProjInfo.zFar = 100.0f;
		pCamera->SetCamera(CameraPos1, CameraTarget1, CameraUp1);
		// Must be done after glut is initialized!
		m_directionalLight.Color = Vector3f(1.0f, 1.0f, 1.0f);
		m_directionalLight.AmbientIntensity = 0.5f;
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		CreateVertexBuffer();
		CreateIndexBuffer();
		loadImg();
		BindTexture();
		//CompileShaders();
		m_pEffect = new lightUtil();

		if (!m_pEffect->Init())
		{
			return false;
		}

		m_pEffect->Enable();
		m_pEffect->SetTextureUnit(0);
		
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

/*
		file_reader(pVSFileName, vs);
		file_reader(pFSFileName, fs);
		AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
		AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);*/

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

		gWorldLocation = glGetUniformLocation(ShaderProgram, "gWVP");
		//assert(gWorldLocation != 0xFFFFFFFF);
	}

	void loadMesh(cyTriMesh &trimesh, const char* filename) {
		trimesh.LoadFromFileObj("teapot.obj");
	}
	void CreateVertexBuffer()
	{
		Vertex* Vertices = new Vertex[meshdata.NV()];
		for (int i = 0; i < meshdata.NV(); i++) {
			Vertices[i].m_pos = Vector3f(
				meshdata.V(i).x,
				meshdata.V(i).y,
				meshdata.V(i).z);
		}

		for (int i = 0; i < meshdata.NF(); i++) {
			for (int j = 0; j < 3; j++) {
				Vertices[meshdata.F(i).v[j]].m_tex =
					cyPoint2f(
						meshdata.VT(meshdata.FT(i).v[j]).x,
						meshdata.VT(meshdata.FT(i).v[j]).y);
			}

		}
		
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * meshdata.NV(), Vertices, GL_STATIC_DRAW);
	}

	void CreateIndexBuffer()
	{
		unsigned int *Indices = new unsigned int[3 * meshdata.NF()];
		/*{
			0, 3, 1,
			1, 3, 2,
			2, 3, 0,
			0, 1, 2 };*/
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

	/*static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
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
*/

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


		m_pEffect->SetWVP(&aMat4);
		m_pEffect->SetDirectionalLight(m_directionalLight);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		//BindTexture();
		glDrawElements(GL_TRIANGLES, meshdata.NF() * 4, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);


		glutSwapBuffers();

		/*glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

		glDrawElements(GL_TRIANGLES, meshdata.NF() * 4, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);

		glutSwapBuffers();*/
	}

	void OnKeyboard(unsigned char Key, int x, int y)
	{
		pCamera->OnKeyboard(Key);
		switch (Key) {
		case 'o':
			m_directionalLight.AmbientIntensity += 0.05f;
			break;

		case 'p':
			m_directionalLight.AmbientIntensity -= 0.05f;
			break;
		}
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