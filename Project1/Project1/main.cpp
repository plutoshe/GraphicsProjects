#ifdef GLEW_STATIC
	#define GLEWAPI extern
#else
#ifdef GLEW_BUILD
	#define GLEWAPI extern __declspec(dllexport)
#else
	#define GLEWAPI extern __declspec(dllimport)
#endif
#endif
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<iostream>

using namespace std;

void changeViewport(int w, int h)
{
	glViewport(0, 0, w, h);
}

void render()
{
	glClearColor(0, 0.5, 0.3, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}

void idleFunc() {}

void processNormalKeys(unsigned char key, int x, int y) {
	printf("%d", key);
	if (key == 27)
		exit(0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("LJLHelloWord");
	glutReshapeFunc(changeViewport);
	glutDisplayFunc(render);
	glutIdleFunc(idleFunc);
	glutKeyboardFunc(processNormalKeys);

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		printf("GLEW ERROR");
		return 1;
	}

	glutMainLoop();

	return 0;

}