#ifndef GAME_H
#define GAME_H
#include "game.h"

Game::Game() {
	graphics = new Graphics();
}

Game::~Game() {
	delete graphics;
	graphics = nullptr;
}

Game& Game::instance() {
	static Game instance;
	return instance;
}

void Game::init() {
	currTime = clock();
	
	Camera::instance().setPosition(0, 3,-10); 
	Camera::instance().setLookAt(0, 3, 0);

	graphics->init();

	Model loadingScreen = Model();
	loadingScreen.clearModel();
	loadingScreen.loadModel("../assets/models/sm_plane.obj");
	loadingScreen.loadTexture("../assets/textures/t_loading.png");
	loadingScreen.buildGeometryBuffers(graphics->Program());
	
	glDisable(GL_CULL_FACE);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(graphics->Program());
	loadingScreen.render(graphics->Program(), false);
	glutSwapBuffers();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	Camera::instance().setPosition(-30, 30, -30);
	Camera::instance().setLookAt(20, 3, 20);

	Map::instance().readMap("../assets/maps/demo-pmap.pmap");
	Map::instance().buildHexGeometryBuffers(graphics->Program());

	this->aManager->initAwesomium();
}

void Game::update() {
	clock_t endTime = clock();

	double elapsedSeconds = double(endTime - currTime) / FPS;

	if (elapsedSeconds >= timer) {
		currTime = endTime;
		/*cnt = 0;
		index++;
		if (index >= graphics->gCubes.GetSize()) {
			index = 0;
		}
		graphics->cube.position.x = graphics->gCubes.GetCopyAt(index).x;
		graphics->cube.position.y = graphics->gCubes.GetCopyAt(index).y;*/
		glutPostRedisplay();
	}
}

void Game::render() {
	graphics->render();
}
#endif