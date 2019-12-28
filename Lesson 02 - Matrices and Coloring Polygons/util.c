#include <stdio.h>
#include <stdlib.h>

#include "util.h"

static int     gcolormode = COLOR_MODE_CYAN;
static GLfloat gprojscale = 1.0f;

void initGL()
{
	// initialize projrction matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f, -1.0f);

	// initialize modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// initialize clear color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// check for error
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		fprintf(stderr, "Error initialising OpenGL: %s\n",
			gluErrorString(error));
		exit(EXIT_FAILURE);
	}
}

void update()
{
	
	
}

void render()
{
	// clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	// reset model view matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// move to the center of screen
	glTranslatef(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);

	if (gcolormode == COLOR_MODE_CYAN) {
		// solid cyan
		glBegin(GL_QUADS);
			glColor3f(0.0f, 1.0f, 1.0f);
			glVertex2f(-50.0f, -50.0f);
			glVertex2f( 50.0f, -50.0f);
			glVertex2f( 50.0f,  50.0f);
			glVertex2f(-50.0f,  50.0f);
		glEnd();
	}
	else {
		// solid cyan
		glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-50.0f, -50.0f);
			glColor3f(1.0f, 1.0f, 0.0f); glVertex2f( 50.0f, -50.0f);
			glColor3f(0.0f, 1.0f, 0.0f); glVertex2f( 50.0f,  50.0f);
			glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(-50.0f,  50.0f);
		glEnd();
	}

	glLoadIdentity();
	
	glBegin(GL_POINTS); 
		int i;
		for (i=0; i<60; i+=2) {
			glColor3f(0.0f, 1.0f, 1.0f);
			glVertex2f(i, i);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2f(SCREEN_WIDTH - i, SCREEN_HEIGHT - i);
		}
	glEnd();


	// update screen
	glutSwapBuffers();
}

void handlekeys(unsigned char key, int x, int y)
{
	if (key =='q') {
		gcolormode = (gcolormode == COLOR_MODE_CYAN)
			? COLOR_MODE_MULTI
			: COLOR_MODE_CYAN;
	}
	else if(key == 'e') {
		
		if (gprojscale > 5.0f) {
			gprojscale = 1.0f;
		}

		// update projection matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0f, SCREEN_WIDTH * gprojscale,
			SCREEN_HEIGHT * gprojscale, 0.0f, 1.0f, -1.0f);
		gprojscale += 2.0f;
		
	}
}
