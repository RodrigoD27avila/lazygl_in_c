#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "texture.h"
#include "rect.h"

struct Texture *gtexture;
struct Rect    gclips[4];

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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glCullFace(GL_BACK);

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

	ilInit();
	ilClearColor(255, 255, 255, 000);
	ILenum ilerror = ilGetError();
	if (ilerror != IL_NO_ERROR) {
		fprintf(stderr, "Unable to init DevIL.\n");
		exit(EXIT_FAILURE);
	}
}

void load()
{
	gtexture = (struct Texture *)malloc(sizeof(struct Texture));
	textureLoadFromFile(gtexture, "texture.png");

	double w = (double)gtexture->w / 2;
	double h = (double)gtexture->h / 2;

	gclips[0].x = 0.0f;
	gclips[0].y = 0.0f;
	gclips[0].w = w;
	gclips[0].h = h;
	
	gclips[1].x = w;
	gclips[1].y = 0.0f;
	gclips[1].w = w;
	gclips[1].h = h;
	
	gclips[2].x = 0.0f;
	gclips[2].y = h;
	gclips[2].w = w;
	gclips[2].h = h;
	
	gclips[3].x = w;
	gclips[3].y = h;
	gclips[3].w = w;
	gclips[3].h = h;
}

void update()
{
	
	
}

void render()
{
	// clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	GLuint x1 = 0.0f;
	GLuint y1 = 0.0f;

	GLuint x2 = SCREEN_WIDTH  - gclips[1].w;
	GLuint y2 = 0.0f;

	GLuint x3 = 0.0f; 
	GLuint y3 = SCREEN_HEIGHT - gclips[2].h;
	
	GLuint x4 = SCREEN_WIDTH  - gclips[3].w;
	GLuint y4 = SCREEN_HEIGHT - gclips[3].h;

	textureRender(gtexture, x1, y1, &gclips[0]);
	textureRender(gtexture, x2, y2, &gclips[1]);
	textureRender(gtexture, x3, y3, &gclips[2]);
	textureRender(gtexture, x4, y4, &gclips[3]);

	// update screen
	glutSwapBuffers();
}

void handlekeys(unsigned char key, int x, int y)
{
	if (key =='q') {
	}
}
