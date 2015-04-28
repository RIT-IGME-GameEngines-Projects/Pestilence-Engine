#ifndef _MODEL_H_
#define _MODEL_H_

#define M_PI           3.14159265358979323846 
#define DEG2RAD		   M_PI / 180
#define PI360		   M_PI / 360

#include <vector>
#include <iostream>
#include <cmath>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/GL.h>
#include <SOIL.h>

#include "dataStructures\matrix4.h"
#include "sse\quaternionX.h"
#include "dataStructures\modelStructures.h"
#include "ObjLoader.h"

#include "glm/glm.hpp"

using namespace std;
using namespace glm;

class Model{

public:
	Model();
	Model(Vector3 pos, Vector3 scal, Euler3 angle);
	~Model();

	void loadModel(char* filename);
	void clearModel();

	void loadTexture(char* filename);
	void setUpTexture(GLuint program);

	void buildGeometryBuffers();
	void render(GLuint program);

	void scale(float x, float y, float z, GLuint program);
	void translate(float x, float y, float z, GLuint program);
	void rotate(float yaw, float pitch, float roll, GLuint program);

	Vector3 position;
	Vector3 scalem;
	Euler3 angles;

	vector<vec3> vertices;
	vector<vec2> uvs;
	vector<vec3> normals;

private:
	QuaternionX rotx;
	GLuint vertexBuffer, uvBuffer;
	GLuint texture;
};

#endif