#include "matrix4.h"

#include "modelStructures.h"

Matrix4::Matrix4(float m00, float m10, float m20, float m30,
	float m01, float m11, float m21, float m31,
	float m02, float m12, float m22, float m32,
	float m03, float m13, float m23, float m33) {

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

Matrix4 Matrix4::Identity = Matrix4(1, 0, 0, 0,
									0, 1, 0, 0,
									0, 0, 1, 0,
									0, 0, 0, 1);

Matrix4 Matrix4::Translate(float x, float y, float z)
{
	Matrix4 mat = Matrix4(1, 0, 0, x,
						  0, 1, 0, y,
						  0, 0, 1, z,
						  0, 0, 0, 1);

	return mat;
}

Matrix4 Matrix4::Scale(float x, float y, float z) {
	Matrix4 mat = Matrix4(x, 0, 0, 0,
						  0, y, 0, 0,
						  0, 0, z, 0,
						  0, 0, 0, 1);

	return mat;
}

Matrix4 Matrix4::LookAt(Vector3 position, Vector3 lookat, Vector3 up)
{
	return Matrix4::Identity;
}

Matrix4 Matrix4::Perspective(float fov, float aspect, float near, float far)
{
	float range = near - far;
	float halfFOV = fov * 0.5;
	float tanHalfFOV = tanf(halfFOV * DEG2RAD);

	//Matrix4 mat = Matrix4()

	return Matrix4::Identity;
}

mat4 Matrix4::ToMat4(Matrix4 mat) {
	mat4 outMat = mat4(mat.m00, mat.m01, mat.m02, mat.m03,
		mat.m10, mat.m11, mat.m12, mat.m13,
		mat.m20, mat.m21, mat.m22, mat.m23,
		mat.m30, mat.m31, mat.m32, mat.m33);

	return outMat;
}