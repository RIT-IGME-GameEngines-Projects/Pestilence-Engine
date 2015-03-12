#ifndef _QUATERNION_H_
#define _QUATERNION_H_

class Quaternion {
public:
	Quaternion(float u, float x, float y, float z);
	~Quaternion();

	float u, x, y, z;

	static Quaternion Identity;

	static Quaternion euler(float x, float y, float z);
	static Quaternion slerp(Quaternion q1, Quaternion q2, float u);
};

#endif