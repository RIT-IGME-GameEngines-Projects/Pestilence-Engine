#include "lightManager.h"

LightManager& LightManager::instance() {
	static LightManager instance;
	return instance;
}

void LightManager::buildBuffers(GLuint program) {
	m_DirectionalLight.buildBuffers(program);
}

void LightManager::addDirectionalLight(DirectionalLight light) {
	m_DirectionalLight = light;
}

void LightManager::addPointLight(PointLight light) {
	m_PointLights.push_back(light);
}

void LightManager::addSpotLight(SpotLight light) {
	m_SpotLights.push_back(light);
}