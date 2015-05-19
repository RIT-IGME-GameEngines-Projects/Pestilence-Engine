#ifndef _SKYBOX_H_
#define _SKYBOX_H_

#include <vector>

#include "model.h"

using namespace std;

class SkyBox {
public:
	SkyBox();
	~SkyBox();

	void buildSkyBox(char* texturePath);

	void buildSkyBoxBuffers(GLuint program);
	void renderSkyBox(GLuint program);

private:
	Model skyBoxModel;
};

#endif