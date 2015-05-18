#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/GL.h>
#include <SOIL.h>

#include "shaderManager.h"
#include "model.h"
#include "graphics\primitive.h"
#include "Spline.h"
#include "camera.h"
#include "light\lightManager.h"
#include "map.h"

#include "sse\quaternionX.h"

#define BUFFER_OFFSET(i) ((char*)NULL + (i))

class Graphics {
public:
	Graphics();
	~Graphics();

	void init();
	void render();

	void buildGeometryBuffers();

	void buildUnitTest(int countX, int countY, int countZ, char* objfile, char* texturefile);
	void buildUnitTestBuffers();
	void renderUnitTest();

	Model cube;
	Model suzanne1, suzanne2, suzanne3;
	//Primitive cube;
	MyVector<Vector3> gCubes;

private:
	GLuint buffer[1];
	GLuint ebuffer[1];
	int NumElements;

	GLuint program;
	int numVerts[1];

	bool bufferInit = false;

	Spline* spine;

	ObjLoader* objLoader;

	GLuint m_VertexArray, m_VertexBuffer;
	vector<vec3> vertices;

	vector<Model> unitTestModels;
};

#endif