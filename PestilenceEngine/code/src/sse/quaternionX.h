#ifndef _QUATERNIONX_H_
#define _QUATERNIONX_H_

#define M_PI           3.14159265358979323846 
#define PI360		   M_PI / 360

#include <math.h>
#include <xmmintrin.h>

#include "../dataStructures/matrix4.h"

class QuaternionX {
public:
	QuaternionX();
	QuaternionX(float w, float x, float y, float z);
	~QuaternionX();

	__m128 quatData;

	static QuaternionX Identity;

	static float getFloat(__m128 V, unsigned int i);
	static float* toArray(__m128 V);

	static Matrix4 toMatrix(__m128 quat);
	static QuaternionX euler(float yaw, float pitch, float roll);
	static QuaternionX slerp(__m128 q1, __m128 q2, float u);
};

#endif