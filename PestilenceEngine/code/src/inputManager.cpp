#include "inputManager.h"

InputManager::InputManager() { }

InputManager::~InputManager() {
	release();
}

InputManager& InputManager::instance() {
	static InputManager instance;
	return instance;
}

void InputManager::release() {

}

void InputManager::keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 033:
		exit(0);
		break;

	case '4':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;

	case '5':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;

	case '3':
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	}
}