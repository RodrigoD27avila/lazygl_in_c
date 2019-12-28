#include "opengl.h"

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS    =  60;

const int COLOR_MODE_CYAN  = 0;
const int COLOR_MODE_MULTI = 1;

void initGL();
void update();
void render();
void handlekeys(unsigned char key, int x, int y);
