#ifndef _POINTLIGHT_H_
#define _POINTLIGHT_H_

#include "glm/glm.hpp"

using namespace glm;

class PointLight {
public:
	PointLight() {
		m_Position = vec3(); 
		m_Radius = 1;
		m_Color = vec3(1, 1, 1);
	};

	PointLight(vec3 pos, vec3 color, float radius) { 
		m_Position = pos; 
		m_Radius = radius;
		m_Color = color;
	};

	~PointLight(){};

private:
	vec3 m_Position;
	float m_Radius;
	vec3 m_Color;
};

#endif