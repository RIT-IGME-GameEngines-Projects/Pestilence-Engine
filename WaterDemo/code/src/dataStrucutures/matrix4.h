#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include <stdio.h>
#include <iostream>

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

	static float* ToMat4(Matrix4 mat);
};

#endif