#include "quaternion.h"

Quaternion Quaternion::Identity = Quaternion(0.0f, 0.0f, 0.0f, 0.0f);

Quaternion::Quaternion(float w, float x, float y, float z) {
	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;
}

Quaternion::~Quaternion() {

}

Quaternion Quaternion::euler(float yaw, float pitch, float roll) {
	Quaternion q = Quaternion::Identity;

	float c1 = cos(yaw*0.5);
	float s1 = sin(yaw*0.5);
	float c2 = cos(pitch*0.5);
	float s2 = sin(pitch*0.5);
	float c3 = cos(roll*0.5);
	float s3 = sin(roll*0.5);
	float c1c2 = c1*c2;
	float s1s2 = s1*s2;

	float w = c1c2*c2 - s1s2*s3;
	float x = c1c2*s3 + s1s2*c3;
	float y = s1*c2*c3 + c2*s2*s3;
	float z = c1*s2*c3 - s1*c2*s3;

	q = Quaternion(w, x, y, z);

	return q;
}

Quaternion Quaternion::slerp(Quaternion q1, Quaternion q2, float u) {
	Quaternion q = Quaternion::Identity;

	//Calculate angle between lines
	float cosHalfTheta = q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;

	if (abs(cosHalfTheta) >= 1.0f) {
		q.w = q1.w; q.x = q1.x; q.y = q1.y; q.z = q1.z;
		return q;
	}

	float halfTheta = acos(cosHalfTheta);
	float sinHalfTheta = sqrt(1.0 - cosHalfTheta* cosHalfTheta);

	if (fabs(sinHalfTheta) < 0.001) {
		q.w = (q1.w * 0.5 + q2.w * 0.5);
		q.x = (q1.x * 0.5 + q2.x * 0.5);
		q.y = (q1.y * 0.5 + q2.y * 0.5);
		q.z = (q1.z * 0.5 + q2.z * 0.5);
		return q;
	}

	float ratioA = sin((1 - u) * halfTheta) / sinHalfTheta;
	float ratioB = sin((u*halfTheta) / sinHalfTheta);

	q.w = (q1.w * ratioA + q2.w * ratioB);
	q.x = (q1.x * ratioA + q2.x * ratioB);
	q.y = (q1.y * ratioA + q2.y * ratioB);
	q.z = (q1.z * ratioA + q2.z * ratioB);

	return q;
}

Matrix4 Quaternion::toMatrix(Quaternion quat) {
	Matrix4 mat = Matrix4::Identity;

	float m00 = 1 - (2 * (quat.y * quat.y)) - (2 * (quat.z * quat.z));
	float m10 = (2 * quat.x * quat.y) - (2 * quat.z * quat.w);
	float m20 = (2 * quat.x * quat.z) + (2 * quat.y * quat.w);
	float m30 = 1.0f;

	float m01 = (2 * quat.x * quat.y) + (2 * quat.z * quat.w);
	float m11 = 1 - (2 * (quat.x * quat.x)) - (2 * (quat.z * quat.z));
	float m21 = (2 * quat.y * quat.z) - (2 * quat.x * quat.w);
	float m31 = 1.0f;

	float m02 = (2 * quat.x * quat.z) - (2 * quat.y * quat.y);
	float m12 = (2 * quat.y * quat.z) + (2 * quat.x * quat.w);
	float m22 = 1 - (2 * (quat.x * quat.x)) - (2 * quat.y * quat.y);
	float m32 = 1.0f;

	float m03 = 1.0f;
	float m13 = 1.0f;
	float m23 = 1.0f;
	float m33 = 1.0f;

	mat = Matrix4(m00, m01, m02, m03,
				m10, m11, m12, m13,
				m20, m21, m22, m23,
				m30, m31, m32, m33);

	return mat;
}