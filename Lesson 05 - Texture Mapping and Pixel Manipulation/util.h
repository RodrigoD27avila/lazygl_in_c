#include "opengl.h"

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS    =  60;

void initGL();
void load();
void update();
void render();
void handlekeys(unsigned char key, int x, int y);
