#ifndef MODELSTRUCTURES_H
#define MODELSTRUCTURES_H

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