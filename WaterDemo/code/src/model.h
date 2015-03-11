#ifndef _MODEL_H_
#define _MODEL_H_

#include <vector>
#include <iostream>
#include <cmath>
#include <stdio.h>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/GL.h>
#include <SOIL.h>

using namespace std;

class Model{

public:
	Model();
	~Model();

	void makeCube();

	void clearModel();

	void addTriangle(float x0, float y0, float z0, float u0, float v0,
		float x1, float y1, float z1, float u1, float v1,
		float x2, float y2, float z2, float u2, float v2);

	void loadTexture(char* filename);
	void setUpTexture(GLuint program);

	GLushort *getIndices();

	float *getVertices();
	float *getNormals();
	float *getUV();

	int nVertices();

private:
	vector<float> points;
	vector<float> normals;
	vector<float> uv;
	float *pointArray = 0;
	float *normalArray = 0;
	float *uvArray = 0;
	GLushort *indexArray = 0;
};

#endif