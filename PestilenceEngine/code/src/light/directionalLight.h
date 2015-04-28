#ifndef _DIRECTIONALLIGHT_H_
#define _DIRECTIONALLIGHT_H_

#include "glm/glm.hpp"

using namespace glm;

class DirectionalLight {
public:
	DirectionalLight() {
		m_Direction = vec3();
		m_Color = vec3(1, 1, 1);
	}

	DirectionalLight(vec3 direction, vec3 color) {
		m_Direction = direction;
		m_Color = color;
	}

private:
	vec3 m_Direction;
	vec3 m_Color;
};

#endif