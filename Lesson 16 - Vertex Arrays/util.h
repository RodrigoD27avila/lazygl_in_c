#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include "opengl.h"

#include <IL/il.h>
#include <IL/ilu.h>

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SCREEN_FPS     60

void initGL();
void load();
void update();
void render();
void handlekeys(unsigned char key, int x, int y);

#endif // UTIL_H_INCLUDED
