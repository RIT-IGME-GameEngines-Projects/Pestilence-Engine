#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/GL.h>
#include <SOIL.h>

#include "shaderManager.h"
#include "model.h"
#include "Spline.h"

#include "sse\quaternionX.h"

#define BUFFER_OFFSET(i) ((char*)NULL + (i))

class Graphics {
public:
	Graphics();
	~Graphics();

	void init();
	void render();

	void buildGeometryBuffers();

	void createCube();
	void createGCubes();

	Model cube;
	MyVector<Vector3> gCubes;

private:
	GLuint buffer[1];
	GLuint ebuffer[1];
	int NumElements;

	GLuint program;
	int numVerts[1];

	bool bufferInit = false;

	Spline* spine;
};

#endif