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
#include "dataStructures\quaternion.h"
#include "dataStructures\modelStructures.h"

using namespace std;

class Model{

public:
	Model();
	~Model();

	void makeCube();
	void makePlane();
	void makeStrip();

	void clearModel();

	void pointShiftTest();
	void pointShiftByLocation(float x, float y, float z);

	void addTriangle(float x0, float y0, float z0, float u0, float v0,
		float x1, float y1, float z1, float u1, float v1,
		float x2, float y2, float z2, float u2, float v2);

	void loadTexture(char* filename);
	void setUpTexture(GLuint program);

	void scalem(float x, float y, float z, GLuint program);
	void translate(float x, float y, float z, GLuint program);
	void rotate(float yaw, float pitch, float roll, GLuint program);

	//void rotate()

	GLushort *getIndices();

	float *getVertices();
	float *getNormals();
	float *getUV();

	int nVertices();

	Vector3 position;
	Vector3 scale;
	Euler3 angles;

private:
	vector<float> points;
	vector<float> normals;
	vector<float> uv;
	float *pointArray = 0;
	float *normalArray = 0;
	float *uvArray = 0;
	GLushort *indexArray = 0;

	vector<Face> faces;
	Face* faceArray = 0;

	Quaternion rotation;
};

#endif