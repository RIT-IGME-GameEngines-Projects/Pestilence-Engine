#include "quaternion.h"

Quaternion Quaternion::Identity = Quaternion(0.0f, 0.0f, 0.0f, 0.0f);

Quaternion::Quaternion(float u, float x, float y, float z) {
	this->u = u;
	this->x = x;
	this->y = y;
	this->z = z;
}

Quaternion::~Quaternion() {

}

Quaternion Quaternion::euler(float x, float y, float z) {
	Quaternion q = Quaternion::Identity;

	return q;
}

Quaternion Quaternion::slerp(Quaternion q1, Quaternion q2, float u) {
	Quaternion q = Quaternion::Identity;

	return q;
}