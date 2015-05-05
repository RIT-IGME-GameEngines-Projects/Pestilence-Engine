#ifndef _LIGHTMANAGER_H_
#define _LIGHTMANAGER_H_

#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/GL.h>

#include "lights.h"

using namespace std;

class LightManager {

public:
	~LightManager();

	static LightManager& instance();

	void buildBuffers(GLuint program);

	void addDirectionalLight(DirectionalLight light);
	void addSpotLight(SpotLight light);
	void addPointLight(PointLight light);

	vector<PointLight> PointLights() { return m_PointLights; };
	vector<SpotLight> SpotLights() { return m_SpotLights; };
	DirectionalLight Sun() { return m_DirectionalLight; };

	GLuint DirLightLoc() { return m_DirLightLoc; };

private:
	LightManager();

	vector<PointLight> m_PointLights;
	vector<SpotLight> m_SpotLights;
	DirectionalLight m_DirectionalLight;

	GLuint m_DirLightLoc;
};

#endif