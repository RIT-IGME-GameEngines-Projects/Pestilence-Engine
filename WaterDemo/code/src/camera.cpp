#include "camera.h"

Camera::Camera() {

}

Camera::Camera(float fov, float aspect, float near, float far) {
	m_fov = fov;
	m_aspect = aspect;
	m_near = near;
	m_far = far;
}

Camera::~Camera() {

}