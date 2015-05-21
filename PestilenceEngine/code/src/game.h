#ifndef _GAME_H_
#define _GAME_H_

#include "graphics.h"
#include "logger.h"
#include "map.h"
#include "utils\awesomiumManager.h"

using namespace Awesomium;

#define FPS  60

class Game {
public:
	~Game();

	static Game& instance();

	void init();
	void update();
	void render();

private:
	Game();

	Graphics* graphics;
	awesomiumManager* aManager;
	clock_t currTime;
	int index = 0;
	int cnt = 0;
	float timer = 0.1;

	Logger* logger;
}; 

#endif