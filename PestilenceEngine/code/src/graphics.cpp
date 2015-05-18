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

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	LightManager::instance().addDirectionalLight(DirectionalLight(vec3(4, 4, 4), vec3(1, 1, 1), 25.0f));

	/*suzanne1 = Model();
	suzanne1.clearModel();
	suzanne1.loadModel("../assets/models/sm_suzanne.obj");
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
	Map::instance().buildHexGeometryBuffers(program);
}


void Graphics::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(program);

	/*suzanne1.render(program);
	suzanne2.render(program);
	suzanne3.render(program);
	cube.render(program);*/
	Map::instance().renderHex(program);

	glutSwapBuffers();
}


void Graphics::createCube() {
	
}

void Graphics::createGCubes() {
	for (int i = 0; i < spine->graphPoints->GetSize(); i++)
	{
		Vector3 currPt = *(spine->graphPoints->GetCopyAt(i));
		if (i == 0)
		{
			cube.position.x = currPt.x;
			cube.position.y = currPt.y;
		}
		//Model m = Model();
		//m.clearModel(); 
		//m.makeCube(); 
		//m.translate(currPt.x, currPt.y, currPt.z, program);
		gCubes.Push(currPt);
	}
	buildGeometryBuffers();
}