#include "opengl.h"

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS    =  60;

enum ViewPortMode {
	VIEW_PORT_MODE_FULL,
	VIEW_PORT_MODE_HALF_CENTER,
	VIEW_PORT_MODE_HALF_TOP,
	VIEW_PORT_MODE_QUAD,
	VIEW_PORT_MODE_RADAR,
};

void initGL();
void update();
void render();
void handlekeys(unsigned char key, int x, int y);
