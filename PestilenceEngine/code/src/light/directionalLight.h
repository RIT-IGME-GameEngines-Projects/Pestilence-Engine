#ifndef _DIRECTIONALLIGHT_H_
#define _DIRECTIONALLIGHT_H_

#include <GL/GL.h>
#include "glm/glm.hpp"

using namespace glm;

class DirectionalLight {
public:
	DirectionalLight() {
		m_Position = vec3();
		m_Color = vec3(1, 1, 1);
	}

	DirectionalLight(vec3 position, vec3 color) {
		m_Position = position;
		m_Color = color;
	}

	void buildBuffers(GLuint program) {
		m_DirLoc = glGetUniformLocation(program, "w_lightPos");
		m_ColorLoc = glGetUniformLocation(program, "lightColor");
		m_PowerLoc = glGetUniformLocation(program, "lightPower");
	}

	GLuint DirLoc() { return m_DirLoc; };
	GLuint ColorLoc() { return m_ColorLoc; };
	GLuint PowerLoc() { return m_PowerLoc; };

private:
	vec3 m_Position;
	vec3 m_Color;
	float m_Power;


	GLuint m_DirLoc, m_ColorLoc, m_PowerLoc;
};

#endif