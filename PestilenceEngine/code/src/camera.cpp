#include "camera.h"

Camera::Camera() {
	m_Projection = perspective(m_FOV, m_Aspect, m_Near, m_Far);
	m_View = mat4();
	m_World = mat4(1.0f);
	m_Position = vec3(4, 3, 3);
	m_Forward = vec3(0, 0, 0);
	m_Up = vec3(0, 1, 0);
}

Camera::~Camera() {

}

Camera& Camera::instance() {
	static Camera instance;
	return instance;
}

void Camera::keyboard(unsigned char key, int x, int y) {

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