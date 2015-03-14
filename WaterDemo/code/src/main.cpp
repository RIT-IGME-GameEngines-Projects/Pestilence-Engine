#include <cstdlib>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/GL.h>
#include <SOIL.h>

#include "shaderManager.h"
#include "model.h"
#include "sse\quaternionX.h"

using namespace std;

#define BUFFER_OFFSET(i) ((char*)NULL + (i))

GLuint buffer[1];
GLuint ebuffer[1];
int NumElements;

GLuint program;
int numVerts[1];

bool bufferInit = false;

Model cube;

void render() {
	NumElements = cube.nVertices();
	float* points = cube.getVertices();
	int dataSize = cube.nVertices() * 4 * sizeof(float);
	float* texCoords = cube.getUV();
	int tdataSize = cube.nVertices() * 2 * sizeof(float);
	GLushort* elements = cube.getIndices();
	int edataSize = cube.nVertices() * sizeof(GLushort);

	glGenBuffers(1, &buffer[0]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);

	glBufferData(GL_ARRAY_BUFFER, dataSize + tdataSize, 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, points);
	glBufferSubData(GL_ARRAY_BUFFER, dataSize, tdataSize, texCoords);

	glGenBuffers(1, &ebuffer[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebuffer[0]);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, edataSize, elements, GL_STATIC_DRAW);

	numVerts[0] = cube.nVertices();
}

void idle() {
	
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebuffer[0]);

	glUseProgram(program);

	int dataSize = numVerts[0] * 4 * sizeof(float);
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint vTexCoords = glGetAttribLocation(program, "vTexCoord");
	glEnableVertexAttribArray(vTexCoords);
	glVertexAttribPointer(vTexCoords, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(dataSize));

	cube.setUpTexture(program);

	glDrawElements(GL_TRIANGLES, numVerts[0], GL_UNSIGNED_SHORT, (void*)0);

	glutSwapBuffers();
}


void createCube() {
	cube = Model();
	cube.clearModel();

	cube.makeCube();
	//cube.makePlane();
	//cube.makeStrip();

	render();
}

void init()
{
	program = shaderSetup("../assets/shaders/vshader.glsl", "../assets/shaders/fshader.glsl");
	if (!program) {
		cerr << "Error setting up shaders - " << errorString(shaderErrorCode) << endl;

		exit(1);
	}
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	QuaternionX quat1 = QuaternionX(10, 0, 5, 2);
	QuaternionX q1 = quat1.euler(45, 30, 0);
	QuaternionX quat2 = QuaternionX();
	QuaternionX q2 = quat2.euler(50, 100, 20);
	QuaternionX result = QuaternionX::slerp(q1.quatData, q2.quatData, 0);

	Quaternion rquat1 = Quaternion();
	Quaternion rq1 = rquat1.euler(45, 30, 0);
	Quaternion rquat2 = Quaternion();
	Quaternion rq2 = rquat2.euler(50, 100, 20);
	Quaternion rresult = Quaternion::slerp(rq2, rq2, 0);

	createCube();

	cube.loadTexture("../assets/textures/dirt.jpg");
}


void keyboard(unsigned char key, int x, int y)
{
	float rotateAmt = 5;
	float translateAmt = 0.1;

	switch (key) {
	case 033:
		exit(0);
		break;

	case '4':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;

	case '5':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;

	case '3':
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;

	case 'w':
		cube.translate(0, translateAmt, 0, program);
		break;
	case 's':
		cube.translate(0, -translateAmt, 0, program);
		break;
	case 'a':
		cube.translate(-translateAmt, 0, 0, program);
		break;
	case 'd':
		cube.translate(translateAmt, 0, 0, program);
		break;
	case 'q':
		cube.translate(0, 0, -translateAmt, program);
		break;
	case 'e':
		cube.translate(0, 0, translateAmt, program);
		break;

	case 'i':
		cube.rotate(0, -rotateAmt, 0, program);
		break;
	case 'k':
		cube.rotate(0, rotateAmt, 0, program);
		break;
	case 'j':
		cube.rotate(rotateAmt, 0, 0, program);
		break;
	case 'l':
		cube.rotate(-rotateAmt, 0, 0, program);
		break;
	case 'u':
		cube.rotate(0, 0, rotateAmt, program);
		break;
	case 'o':
		cube.rotate(0, 0, -rotateAmt, program);
		break;
	}


	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("SLERP Demo");

	init();

	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
}