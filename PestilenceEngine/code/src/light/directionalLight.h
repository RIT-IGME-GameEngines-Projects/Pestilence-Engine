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
		m_Power = 25.0f;
	}

	DirectionalLight(vec3 position, vec3 color, float power) {
		m_Position = position;
		m_Color = color;
		m_Power = power;
	}

	void buildBuffers(GLuint program) {
		m_DirLoc = glGetUniformLocation(program, "w_lightPos");
		m_ColorLoc = glGetUniformLocation(program, "lightColor");
		m_PowerLoc = glGetUniformLocation(program, "lightPower");
	}

	GLuint DirLoc() { return m_DirLoc; };
	GLuint ColorLoc() { return m_ColorLoc; };
	GLuint PowerLoc() { return m_PowerLoc; };

	vec3 Position() { return m_Position; };
	vec3 Color() { return m_Color; };
	float Power() { return m_Power; };

private:
	vec3 m_Position;
	vec3 m_Color;
	float m_Power;

	GLuint m_DirLoc, m_ColorLoc, m_PowerLoc;
};

#endif