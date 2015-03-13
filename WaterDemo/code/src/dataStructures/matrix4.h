#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#define M_PI           3.14159265358979323846 
#define DEG2RAD		   M_PI / 180

#include <stdio.h>
#include <iostream>

struct Vector3;

class Matrix4 {
public:
	Matrix4(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);
	~Matrix4();

	float m00, m10, m20, m30,
		m01, m11, m21, m31,
		m02, m12, m22, m32,
		m03, m13, m23, m33;

	static Matrix4 Identity;

	static Matrix4 Translate(float x, float y, float z);

	static float* ToMat4(Matrix4 mat);

	static Matrix4 LookAt(Vector3 pos, Vector3 lookat, Vector3 up);
	static Matrix4 Perspective(float fov, float aspect, float near, float far);
};

#endif