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
#include<iostream>
#include <fstream>
#include <cstdio> 
#include <cstdlib>
#include <math.h>
#include<GL/glew.h>
#include<GL/freeglut.h>


#include "cyTriMesh.h"
#include "cyPoint.h"
#include "Log.h"
#include "Vector3f.h"
#include "glApplicationState.h"

using namespace std;

cyTriMesh meshData;
const char* pVSFileName = "shader.vs";
const char* pFSFileName = "shader.fs";
GLuint VBO;
GLuint ShaderProgram;
glApplicationState astate = glApplicationState();
int inputColorLocation = 0;
int viewportPositionLocation, viewportRotationLocation;

const int num = 3892;

void changeViewport(int w, int h)
{
	glViewport(0, 0, w, h);
}

void render()
{
	/*DEBUG_LOG("%.3f %.3f %.3f\n", astate.currentView.x + astate.deltaX,
		astate.currentView.y + astate.deltaY,
		astate.currentView.z);*/
	DEBUG_LOG("currentPosition: %.3f %.3f %.3f\n", astate.currentPosition.x, astate.currentPosition.y, astate.currentPosition.z);
	DEBUG_LOG("instantPosition: %.3f %.3f %.3f\n", astate.instantPosition.x, astate.instantPosition.y, astate.instantPosition.z);
	DEBUG_LOG("currentRotation: %.3f %.3f %.3f\n", astate.currentRotation.x, astate.currentRotation.y, astate.currentRotation.z);
	DEBUG_LOG("instantRotation: %.3f %.3f %.3f\n", astate.instantRotation.x, astate.instantRotation.y, astate.instantRotation.z);

	Vector3f realtimePosition = astate.currentPosition + astate.instantPosition;
	Vector3f realtimeRotation = astate.currentRotation + astate.instantRotation;
//	GLfloat pos[] = { realtimePosition.x, realtimePosition.y, realtimePosition.z };
	glUniform3f(viewportPositionLocation,
		realtimePosition.x,
		realtimePosition.y,
		realtimePosition.z);
	//Vector4f rot = glApplicationState::FromAxis(Vector3f(0, 1, 0), 90 ).normalized();
	Vector4f rot = glApplicationState::QuaternionFromEuler(0, 0, 90);
	DEBUG_LOG("QuaternionFromEuler: %.3f %.3f %.3f %.3f\n", rot.x, rot.y, rot.z, rot.w);
	rot = glApplicationState::QuaternionMultiply(
		glApplicationState::FromAxis(Vector3f(0, 0, 1), realtimeRotation.x).normalized(),
		glApplicationState::FromAxis(Vector3f(0, 1, 0), realtimeRotation.z).normalized()).normalized();
	DEBUG_LOG("Rotation: %.3f %.3f %.3f %.3f\n", rot.x, rot.y, rot.z, rot.w); 
	
	glUniform4f(viewportRotationLocation, rot.x, rot.y, rot.z, rot.w);

	glClear(GL_COLOR_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_POINTS, 0, meshData.NV());
	glDisableVertexAttribArray(0);
	glutSwapBuffers();
}

void CreateVertexBuffer()
{
	
	Vector3f Vertices[num];
	// 将点置于屏幕中央
	cy::Point3f *v = meshData.GetVerticesArray();
	for (int i = 0; i < num; i++) {
		Vertices[i] = Vector3f(v[i].x, v[i].y, v[i].z);
		//multPointMatrix(Vertices[i], Vertices[i]);
	}

	// 创建缓冲器
	glGenBuffers(1, &VBO);
	// 绑定GL_ARRAY_BUFFER缓冲器
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 绑定顶点数据
	printf("\n%d\n", sizeof(Vertices));
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	/*Vector3f Vertices[3];
	Vertices[0] = Vector3f(-1.0f, -1.0f, 1.0f);
	Vertices[1] = Vector3f(1.0f, -1.0f, 7.0f);
	Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);*/
}


void loadVertex(cyTriMesh &trimesh, char* filename) {
	trimesh.LoadFromFileObj(filename);
}


// 使用shader文本编译shader对象，并绑定shader都想到着色器程序中
static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	//
	//1、首先通过hVertexShader = glCreateShader(GL_VERTEX_SHADER)创建着色器对象
	//2、gltLoadShaderFile(szVertexProg,hVertexShader)随后加载着色器文件
	//3、加载之后再进行编译：glComplileShader(hVertexShader)
	//4、创建最终的程序对象：
	//hReturn = glCreateProgram();
	//glAttachShader(hReturn,hVertexShader)
	//glAttachShader(hReturn,hFragmentShader)
	//5、将参数名绑定到指定的参数位置列表上
	//6、绑定之后进行链接：glLinkProgram(hRet)
	//7、链接完成删除之前的顶点着色器和片段着色器glDeleteShader(hVertexShader)
	//8、使用着色器：glUseProgram(myShader)

	// 根据shader类型参数定义两个shader对象
	GLuint ShaderObj = glCreateShader(ShaderType);
	// 检查是否定义成功
	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
		exit(0);
	}

	// 定义shader的代码源
	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);
	glShaderSource(ShaderObj, 1, p, Lengths);
	glCompileShader(ShaderObj);// 编译shader对象

	// 检查和shader相关的错误
	GLint success;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		exit(1);
	}

	// 将编译好的shader对象绑定到program object程序对象上
	glAttachShader(ShaderProgram, ShaderObj);
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
static void CompileShaders()
{
	ShaderProgram = glCreateProgram();
	if (ShaderProgram == 0) {
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}
	string vs, fs;
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

	inputColorLocation = glGetUniformLocation(ShaderProgram, "inputColor");
	viewportPositionLocation = glGetUniformLocation(ShaderProgram, "viewport_pos");
	viewportRotationLocation = glGetUniformLocation(ShaderProgram, "viewport_rot");
	glUseProgram(ShaderProgram);
}


void processMouse(int button, int state, int x, int y) {
	DEBUG_LOG("%d %d %d %d", button, state, x, y);
	astate.aButton = button;
	astate.aState = state;
	astate.ax = x;
	astate.ay = y;
	if (button == 0 && state == 1) {
		astate.SetCurrentPosition(astate.GetCurrentPosition() + astate.instantPosition);
		astate.instantPosition.zero();
	}
	if (button == 2 && state == 1) {
		astate.SetCurrentRotation(astate.GetCurrentRotation() + astate.instantRotation);
		astate.instantRotation.zero();
	}
}
void processMovement(int x, int y) {
	float deltaX = 0;
	float deltaY = 0;
	if (astate.aState == 0) {
		deltaX = x - astate.ax;
		deltaY = y - astate.ay;
	}
	if (astate.aButton == 0) {
		deltaX *= astate.magPosition;
		deltaY *= astate.magPosition;
		astate.instantPosition =
			deltaX * astate.UnitX +
			deltaY * astate.UnitZ;
	}
	else if (astate.aButton == 2) {
		deltaX *= astate.magRotation;
		deltaY *= astate.magRotation;
		astate.instantRotation =
			Vector3f(
				deltaX,
				0,
				deltaY
			);
	}
}

void processNormalKeys(unsigned char key, int x, int y) {
	printf(" Key ID: %d", key);
	if (key == 27)
		exit(0);
	
	if (key == 'w' || key == 'W')
		astate.SetCurrentPosition(astate.currentPosition + Vector3f(0, 0, 1));
	if (key == 's' || key == 'S')
		astate.SetCurrentPosition(astate.currentPosition + Vector3f(0, 0, -1));
	if (key == 'a' || key == 'A')
		astate.SetCurrentPosition(astate.currentPosition + Vector3f(-1, 0, 0));
	if (key == 'd' || key == 'D')
		astate.SetCurrentPosition(astate.currentPosition + Vector3f(1, 0, 0));

	if (key == 'i' || key == 'I')
		astate.SetCurrentRotation(astate.currentRotation + Vector3f(0, 0, 1));
	if (key == 'k' || key == 'K')
		astate.SetCurrentRotation(astate.currentRotation + Vector3f(0, 0, -1));
	if (key == 'j' || key == 'J')
		astate.SetCurrentRotation(astate.currentRotation + Vector3f(-1, 0, 0));
	if (key == 'l' || key == 'L')
		astate.SetCurrentRotation(astate.currentRotation + Vector3f(1, 0, 0));
}

int main(int argc, char** argv) {
	DEBUG_LOG("%s", argv[1]);
	loadVertex(meshData, argv[1]);
	glutInit(&argc, argv);
	// 显示模式：双缓冲、RGBA
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	// 窗口设置
	glutInitWindowSize(1024, 768);      // 窗口尺寸
	glutInitWindowPosition(100, 100);  // 窗口位置
	glutCreateWindow("Hello world");   // 窗口标题
	glutMouseFunc(processMouse);
	glutMotionFunc(processMovement);
	// 开始渲染
	glutDisplayFunc(render);
	glutIdleFunc(render);
	glutKeyboardFunc(processNormalKeys);

	// 检查GLEW是否就绪，必须要在GLUT初始化之后！
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}
	// 缓存清空后的颜色值
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// 创建顶点缓冲器
	CreateVertexBuffer();

	CompileShaders();
	// 通知开始GLUT的内部循环
	glutMainLoop();
	return 0;

}