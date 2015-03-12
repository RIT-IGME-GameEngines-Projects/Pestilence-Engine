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

	return q;
}