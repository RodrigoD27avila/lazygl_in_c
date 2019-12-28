#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "texture.h"
#include "rect.h"

static struct Texture *gtexture;
static GLfloat angle;
static GLenum filter;
static int  combo;

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

	glLoadIdentity();

	switch (combo) {
	case 0:
		glTranslatef(SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f, 0.0f);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glScalef(2.0f, 2.0f, 0.0f);
		glTranslatef(gtexture->w /-2.0f, gtexture->h /-2.0f, 0.0f);
		break;
	case 1:
		glTranslatef(SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f, 0.0f);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glTranslatef(gtexture->w /-2.0f, gtexture->h /-2.0f, 0.0f);
		glScalef(2.0f, 2.0f, 0.0f);
		break;
	case 2:
		glScalef(2.0f, 2.0f, 0.0f);
		glTranslatef(SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f, 0.0f);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glTranslatef(gtexture->w /-2.0f, gtexture->h /-2.0f, 0.0f);
		break;
	case 3:
		glTranslatef(SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f, 0.0f);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glScalef(2.0f, 2.0f, 0.0f);
		break;
	case 4:
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glTranslatef(SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f, 0.0f);
		glScalef(2.0f, 2.0f, 0.0f);
		glTranslatef(gtexture->w /-2.0f, gtexture->h /-2.0f, 0.0f);
		break;
	}

	// render texture
	textureRender(gtexture, 0, 0, NULL);

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

	else if (key == 'w') {
		angle = 0.0f;
		combo = (combo+1) % 5;
	}
}
