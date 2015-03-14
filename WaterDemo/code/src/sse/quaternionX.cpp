#include "quaternionX.h"

QuaternionX QuaternionX::Identity = QuaternionX(1.0f, 0.0f, 0.0f, 0.0f);

QuaternionX::QuaternionX() {
	float quat[4] = { 0, 0, 0, 0 };

	quatData = _mm_load_ps(quat);
}

QuaternionX::QuaternionX(float w, float x, float y, float z) {
	float quat[4] = { w, x, y, z };

	quatData = _mm_load_ps(quat);
}

QuaternionX::~QuaternionX() {

}

QuaternionX QuaternionX::euler(float yaw, float pitch, float roll) {
	float rawRot[4] = { yaw, pitch, roll, 0 };
	float pi360[4] = { PI360, PI360, PI360, 0 };

	__m128 rot = _mm_load_ps(rawRot);
	__m128 conv = _mm_load_ps(pi360);

	__m128 converted = _mm_mul_ps(rot, conv);

	float h = QuaternionX::getFloat(converted, 0);
	float a = QuaternionX::getFloat(converted, 1);
	float b = QuaternionX::getFloat(converted, 2);

	float c1 = cos(h);
	float s1 = sin(h);
	float c2 = cos(a);
	float s2 = sin(a);
	float c3 = cos(b);
	float s3 = sin(b);

	float w = c1*c2*c3 - s1*s2*s3;
	float x = c1*c2*s3 + s1*s2*c3;
	float y = s1*c2*c3 + c1*s2*s3;
	float z = c1*s2*c3 - s1*c2*s3;

	QuaternionX q = QuaternionX(w, x, y, z);

	return q;
}

QuaternionX QuaternionX::slerp(__m128 q1, __m128 q2, float u) {
	float* q1f = QuaternionX::toArray(q1);
	float* q2f = QuaternionX::toArray(q2);

	float cosHalfTheta = q2f[0] + q1f[1] * q2f[1] + q1f[2] * q2f[2] + q1f[3] * q2f[3];

	if (abs(cosHalfTheta) >= 1.0f) {
		return QuaternionX(q1f[0], q1f[1], q1f[2], q1f[3]);
	}

	float halfTheta = acos(cosHalfTheta);
	float sinHalfTheta = sqrt(1.0 - cosHalfTheta * cosHalfTheta);

	if (fabs(sinHalfTheta) <= 0.001) {
		__m128 scalar = _mm_set1_ps(0.5f);
		q1 = _mm_mul_ps(q1, scalar);
		q2 = _mm_mul_ps(q2, scalar);
		__m128 result = _mm_add_ps(q1, q2);
		float* fResult = QuaternionX::toArray(result);
		return QuaternionX(fResult[0], fResult[1], fResult[2], fResult[3]);
	}

	float ratioA = sin((1 - u) * halfTheta) / sinHalfTheta;
	float ratioB = sin((u*halfTheta) / sinHalfTheta);

	__m128 scalar1 = _mm_set1_ps(ratioA);
	__m128 scalar2 = _mm_set1_ps(ratioB);
	q1 = _mm_mul_ps(q1, scalar1);
	q2 = _mm_mul_ps(q2, scalar2);
	__m128 result = _mm_add_ps(q1, q2);
	float* fResult = QuaternionX::toArray(result);
	return QuaternionX(fResult[0], fResult[1], fResult[2], fResult[3]);
}

float QuaternionX::getFloat(__m128 V, unsigned int i) {
	union {
		__m128 v;
		float a[4];
	} converter;

	converter.v = V;
	return converter.a[i];
}

float* QuaternionX::toArray(__m128 V)
{
	union {
		__m128 v;
		float a[4];
	} converter;

	converter.v = V;
	
	float* result = new float[4];
	result[0] = converter.a[0];
	result[1] = converter.a[1];
	result[2] = converter.a[2];
	result[3] = converter.a[3];

	return result;
}