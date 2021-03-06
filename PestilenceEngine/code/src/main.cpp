#include "game.h"
#include "inputManager.h"

using namespace std;

void update() { Game::instance().update(); }
void render() { Game::instance().render(); }

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Pesilence Engine 0.1.0");
	//glutFullScreen();
	
	Game::instance().init();

	glutIdleFunc(update);
	glutDisplayFunc(render);
	glutKeyboardFunc(InputManager::keyboard);
	glutMouseFunc(InputManager::mouse);

	glutMainLoop();
	//Work on thread-pool / other therading model
}
