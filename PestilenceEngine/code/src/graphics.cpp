#include "graphics.h"

Graphics::Graphics() {

}

Graphics::~Graphics() {

}

void Graphics::init() {
	program = shaderSetup("../assets/shaders/vshader.glsl", "../assets/shaders/fshader.glsl");
	if (!program) {
		cerr << "Error setting up shaders - " << errorString(shaderErrorCode) << endl;

		exit(1);
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);

	LightManager::instance().addDirectionalLight(DirectionalLight(vec3(4, 4, 4), vec3(1, 1, 1), 25.0f));

	/*suzanne1 = Model();
	suzanne1.clearModel();
	suzanne1.loadModel("../assets/models/sm_hexTile.obj");
	suzanne1.loadTexture("../assets/textures/t_suzanne.png");

	suzanne2 = Model();
	suzanne2.clearModel();
	suzanne2.loadModel("../assets/models/sm_suzanne.obj");
	suzanne2.loadTexture("../assets/textures/t_suzanne.png");
	suzanne2.translate(3, 0, 0);
	suzanne2.rotate(90, 90, 90);

	suzanne3 = Model();
	suzanne3.clearModel();
	suzanne3.loadModel("../assets/models/sm_suzanne.obj");
	suzanne3.loadTexture("../assets/textures/t_suzanne.png");
	suzanne3.translate(-3, 0, 0);

	cube = Model();
	cube.clearModel();
	cube.loadModel("../assets/models/sm_crate.obj");
	cube.loadTexture("../assets/textures/t_crate.jpg");
	cube.translate(0, 4, 0);*/

	//buildUnitTest(5, 5, 5, "../assets/models/sm_hexTile.obj", "../assets/textures/t_hexTile_Fallback.png");

	buildGeometryBuffers();
}

void Graphics::buildGeometryBuffers() {
	glGenVertexArrays(1, &m_VertexArray);
	glBindVertexArray(m_VertexArray);

	Camera::instance().buildBuffers(program);

	LightManager::instance().buildBuffers(program);

	/*suzanne1.buildGeometryBuffers(program);
	suzanne2.buildGeometryBuffers(program);
	suzanne3.buildGeometryBuffers(program);
	cube.buildGeometryBuffers(program);*/
	
	//buildUnitTestBuffers();
}


void Graphics::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(program);

	/*suzanne1.render(program);
	suzanne2.render(program);
	suzanne3.render(program);
	cube.render(program);*/
	Map::instance().renderHex(program);
	//renderUnitTest();

	glutSwapBuffers();
}

void Graphics::buildUnitTest(int countX, int countY, int countZ, char* objfile, char* texturefile) {
	for (int x = 0; x < countX; x++) {
		for (int y = 0; y < countY; y++) {
			for (int z = 0; z < countZ; z++) {
				Model m = Model(suzanne1);
				m.loadTexture(texturefile);
				/*m.clearModel();
				m.loadModel(objfile);
				m.loadTexture(texturefile);
				*/
				m.translate(x * 2, y * 2, z * 2);

				unitTestModels.push_back(m);
			}
		}
	}
}

void Graphics::buildUnitTestBuffers() {
	for (int i = 0; i < unitTestModels.size(); i++) {
		unitTestModels[i].buildGeometryBuffers(program);
	}
}

void Graphics::renderUnitTest() {
	for (int i = 0; i < unitTestModels.size(); i++) {
		unitTestModels[i].render(program, true);
	}
}