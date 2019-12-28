#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "texture.h"
#include "rect.h"

struct Texture *gtexture;
GLfloat angle;
GLenum filter;
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
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
}

void update()
{
	angle += 360.0f / SCREEN_FPS;
	if (angle > 360.0f) {
		angle -= 360.0f;
	}	
}

void render()
{
	// clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	GLuint x = (SCREEN_WIDTH  - gtexture->w) / 2.0f;
	GLuint y = (SCREEN_HEIGHT - gtexture->h) / 2.0f;

	textureRender(gtexture, x, y, NULL, angle);

	// update screen
	glutSwapBuffers();
}

void handlekeys(unsigned char key, int x, int y)
{
	if (key =='q') {
		// switch filter
		filter = (filter != GL_LINEAR) ? GL_LINEAR : GL_NEAREST;

		// bind texture for modification
		glBindTexture(GL_TEXTURE_2D, gtexture->id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
