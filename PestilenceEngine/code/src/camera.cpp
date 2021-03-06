#include "camera.h"

Camera::Camera() {
	m_Projection = perspective(m_FOV, m_Aspect, m_Near, m_Far);
	m_View = mat4();
	m_World = mat4(1.0f);
	m_Position = vec3(50, 30, 50);
	m_Forward = vec3(0, 0, 0);
	m_Up = vec3(0, 1, 0);
}

Camera::~Camera() {

}

Camera& Camera::instance() {
	static Camera instance;
	return instance;
}

void Camera::buildBuffers(GLuint program) {
	m_MVPLoc = glGetUniformLocation(program, "MVP");
	m_MLoc = glGetUniformLocation(program, "M");
	m_VLoc = glGetUniformLocation(program, "V");

	m_TranslateLoc = glGetUniformLocation(program, "m_translation");
	m_RotateLoc = glGetUniformLocation(program, "m_rotation");
	m_ScaleLoc = glGetUniformLocation(program, "m_scale");
}

void Camera::setPosition(float x, float y, float z) {
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void Camera::setLookAt(float x, float y, float z) {
	m_Forward.x = x;
	m_Forward.y = y;
	m_Forward.z = z;
}

void Camera::keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'w' | 'W':
		m_Position.z += speed;
		break;
	case 's' | 'S':
		m_Position.z -= speed;
		break;

	case 'a' | 'A':
		m_Position.x -= speed;
		break;
	case 'd' | 'D':
		m_Position.x += speed;
		break;

	case 'q' | 'Q':
		m_Position.y -= speed;
		break;
	case 'e' | 'E':
		m_Position.y += speed;
		break;
	}
}

void Camera::mouse(int button, int state, int x, int y) {

}

mat4 Camera::Projection() {
	return m_Projection;
}

mat4 Camera::View() {
	m_View = lookAt(m_Position, m_Forward, m_Up);
	return m_View;
}

mat4 Camera::World() {
	return m_World;
}

mat4 Camera::MVP() {
	mat4 mvp = Projection() * View() * World();
	return mvp;
}