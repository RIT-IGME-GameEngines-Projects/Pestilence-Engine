#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/GL.h>

#include "camera.h"

class InputManager {
public:
	~InputManager();

	static InputManager& instance();

	void release();

	static void keyboard(unsigned char key, int x, int y);
	static void mouse(int button, int state, int x, int y);

	int i = 0;

private:
	InputManager();
};

#endif