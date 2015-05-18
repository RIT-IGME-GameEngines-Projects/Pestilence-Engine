#include "skyBox.h"

SkyBox::SkyBox() {

}

SkyBox::~SkyBox() {

}

void SkyBox::buildSkyBox(char* texturePath) {
	skyBoxModel = Model();
	skyBoxModel.clearModel();
	skyBoxModel.loadModel("../assets/models/sm_skyBox.obj");
	skyBoxModel.loadTexture(texturePath);
}

void SkyBox::buildSkyBoxBuffers(GLuint program) {
	skyBoxModel.buildGeometryBuffers(program);
}

void SkyBox::renderSkyBox(GLuint program) {
	glCullFace(GL_FRONT);

	skyBoxModel.render(program, false);

	glCullFace(GL_BACK);
}