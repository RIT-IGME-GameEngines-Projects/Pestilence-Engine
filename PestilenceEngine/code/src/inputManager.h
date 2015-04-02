#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/GL.h>

class InputManager {
public:
	static InputManager *instance() {
		if (s_Instance == nullptr) {
			s_Instance = new InputManager();
		}
		return s_Instance;
	}

	void release() {
		delete s_Instance;
		s_Instance = nullptr;
	}

	void keyboard(unsigned char key, int x, int y) {
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

private:
	static InputManager *s_Instance;

	InputManager();
	~InputManager();
};

#endif