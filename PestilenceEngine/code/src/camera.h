#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "dataStructures\modelStructures.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace glm;

class Camera
{
public:
	static Camera& instance();

	void keyboard(unsigned char key, int x, int y);
	void mouse(int button, int state, int x, int y);
	
	mat4 Projection();
	mat4 View();
	mat4 World();
	mat4 MVP();

	~Camera();

private:
	Camera();

	float m_FOV = 60;
	float m_Aspect = 1.333333f;
	float m_Near = 0.01f;
	float m_Far = 1000;

	mat4 m_Projection, m_View, m_World;

	vec3 m_Position, m_Forward, m_Up;
};

#endif