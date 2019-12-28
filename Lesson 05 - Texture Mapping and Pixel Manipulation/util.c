#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "texture.h"

struct Texture *gtexture;

void initGL()
{
	// set viewport
	glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);

	// initialize projrction matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f, -1.0f);

	// initialize modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// initialize clear color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// enabling texture
	glEnable(GL_TEXTURE_2D);

	// check for error
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		fprintf(stderr, "Error initialising OpenGL: %s\n",
			gluErrorString(error));
		exit(EXIT_FAILURE);
	}
}

void load()
{
	// pixels info
	const int checkboard_width  = 128;
	const int checkboard_height = 128;
	const int checkboard_pixel_count =
		checkboard_width * checkboard_height;

	GLuint checkboard[checkboard_pixel_count];

	// go throught pixels
	int i;
	for (i=0; i<checkboard_pixel_count; i++) {

		// get pixel
		GLubyte *colors = (GLubyte *)&checkboard[i];

		if (i / 128 & 16 ^ i % 128 & 16) {
			colors[0] =  0xff;
			colors[1] =  0xff;
			colors[2] =  0xff;
			colors[3] =  0xff;
		}
		else {
			colors[0] =  0xff;
			colors[1] =  0x00;
			colors[2] =  0x00;
			colors[3] =  0xff;
		}

	}

	// load texture
	gtexture = (struct Texture *)malloc(sizeof(struct Texture));
	textureLoadFromPixel32(gtexture, checkboard,
		checkboard_width, checkboard_height);
		
}

void update()
{
	
	
}

void render()
{
	// clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	GLfloat x = (SCREEN_WIDTH  - gtexture->w) / 2.0f;
	GLfloat y = (SCREEN_HEIGHT - gtexture->h) / 2.0f;
	printf("x = %f, y = %f\n", x, y);
	textureRender(gtexture, x, y);

	// update screen
	glutSwapBuffers();
}

void handlekeys(unsigned char key, int x, int y)
{
	if (key =='q') {
	}
}
