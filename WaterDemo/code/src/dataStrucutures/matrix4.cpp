#include "matrix4.h"

Matrix4::Matrix4(float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33) {

	this->m00 = m00;
	this->m01 = m01;
	this->m02 = m02;
	this->m03 = m03;

	this->m10 = m10;
	this->m11 = m11;
	this->m12 = m12;
	this->m13 = m13;

	this->m20 = m20;
	this->m21 = m21;
	this->m22 = m22;
	this->m23 = m23;

	this->m30 = m30;
	this->m31 = m31;
	this->m32 = m32;
	this->m33 = m33;
}

Matrix4::~Matrix4() {

}

Matrix4 Matrix4::Identity = Matrix4(0, 0, 0, 0,
									0, 0, 0, 0,
									0, 0, 0, 0,
									0, 0, 0, 0);

float* Matrix4::ToMat4(Matrix4 mat) {
	float* out = new float[16];

	out[0] = mat.m00;
	out[1] = mat.m01;
	out[2] = mat.m02;
	out[3] = mat.m03;

	out[4] = mat.m10;
	out[5] = mat.m11;
	out[6] = mat.m12;
	out[7] = mat.m13;

	out[8] = mat.m20;
	out[9] = mat.m21;
	out[10] = mat.m22;
	out[11] = mat.m23;

	out[12] = mat.m30;
	out[13] = mat.m31;
	out[14] = mat.m32;
	out[15] = mat.m33;

	return out;
}