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
	graphics->init();
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