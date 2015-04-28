#ifndef _LIGHTMANAGER_H_
#define _LIGHTMANAGER_H_

#include <vector>

#include "lights.h"

using namespace std;

class LightManager {

public:
	~LightManager(){};

	static LightManager& instance(){ return LightManager(); };

private:
	LightManager() {};

	vector<PointLight> m_PointLights;
	vector<SpotLight> m_SpotLights;
	DirectionalLight m_DirectionalLight;
};

#endif