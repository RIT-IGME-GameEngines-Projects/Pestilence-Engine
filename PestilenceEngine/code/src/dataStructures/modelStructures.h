#ifndef _MODEL_STRUCTURES_H_
#define _MODEL_STRUCTURES_H_

#include <iostream>

using namespace std;

struct Point {
	float x;
	float y;
	float z;
	float w;
};

struct UV {
	float u;
	float v;
};

struct Normal {
	float x;
	float y;
	float z;
};

struct Face {
	Point* points;
	UV* uvs;
	Normal* normals;
};

struct FaceIndices {
	float v1, v2, v3;
	float t1, t2, t3;
	float n1, n2, n3;

public:
	FaceIndices(float v1, float v2, float v3,
		float t1, float t2, float t3,
		float n1, float n2, float n3) {
		this->v1 = v1;
		this->v2 = v2;
		this->v3 = v3;

		this->t1 = t1;
		this->t2 = t2;
		this->t3 = t3;

		this->n1 = n1;
		this->n2 = n2;
		this->n3 = n3;
	}

	void print() {
		cout <<  v1 << "/" << t1 << "/" << n1 << " " << v2 << "/" << t2 << "/" << n2 << " " << v3 << "/" << t3 << "/" << n3 << endl;
	}
};

struct Vector2 {
	float x;
	float y;

public:
	Vector2() {
		x = 0; y = 0;
	}

	Vector2(float x, float y) {
		this->x = x;
		this->y = y;
	}
};

struct Vector3 {
	float x;
	float y;
	float z;

public:
	Vector3() {
		x = 0; y = 0; z = 0;
	}

	Vector3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

struct Euler3 {
	float yaw;
	float pitch;
	float roll;

public:
	Euler3(){
		yaw = 0;
		pitch = 0;
		roll = 0;
	}

	Euler3(float yaw, float pitch, float roll) {
		this->yaw = yaw;
		this->pitch = pitch;
		this->roll = roll;
	}
};

#endif