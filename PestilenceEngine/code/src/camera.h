#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "dataStructures\modelStructures.h"

class Camera
{
public:
	Camera();
	Camera(float fov, float aspect, float near, float far);
	~Camera();

private:
	float m_fov, m_aspect, m_near, m_far;
	Vector3 position, lookat, up;
};

#endif