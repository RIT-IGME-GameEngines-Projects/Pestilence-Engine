#include "game.h"
#include "inputManager.h"

using namespace std;

Game game;

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Pesilence Engine 0.01");

	game = Game();
	
	game.init();

	glutIdleFunc(game.update);
	glutDisplayFunc(game.render);
	glutKeyboardFunc(InputManager::keyboard);
	glutMouseFunc(InputManager::mouse);

	glutMainLoop();
}