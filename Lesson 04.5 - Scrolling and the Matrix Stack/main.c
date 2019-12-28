#include "util.h"

static void mainloop(int val);

int main(int argc, char **argv)
{
	// initialize glut
	glutInit(&argc, argv);

	// create a double buffered window
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("OpenGL");

	// do post window/context creation initialization
	initGL();

	// set keyboard handle
	glutKeyboardFunc(handlekeys);

	// set render function
	glutDisplayFunc(render);

	// set main loop
	glutTimerFunc(1000 / SCREEN_FPS, mainloop, 0);

	// start main loop
	glutMainLoop();

	return 0;
}

static void mainloop(int val)
{
	// frame logic
	update();
	render();

	// run frame again
	glutTimerFunc(1000 / SCREEN_FPS, mainloop, val);
}

