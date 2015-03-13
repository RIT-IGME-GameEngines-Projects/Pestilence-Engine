#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#define M_PI           3.14159265358979323846 
#define PI360		   M_PI / 360

#include <math.h>

#include "matrix4.h"

class Quaternion {
public:
	Quaternion();
	Quaternion(float w, float x, float y, float z);
	~Quaternion();

	float w, x, y, z;

	static Quaternion Identity;

	static Matrix4 toMatrix(Quaternion quat);
	static Quaternion euler(float yaw, float pitch, float roll);
	static Quaternion slerp(Quaternion q1, Quaternion q2, float u);
};

#endif