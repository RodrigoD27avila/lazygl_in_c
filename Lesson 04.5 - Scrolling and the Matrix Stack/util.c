#include <stdio.h>
#include <stdlib.h>

#include "util.h"

static GLfloat camerax, cameray;

void initGL()
{
	// initialize projrction matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f, -1.0f);

	// initialize modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// save the default modelview matrix
	glPushMatrix();

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
	glPopMatrix();

	// save matrix;
	glPushMatrix();

	// move to the center of the screen
	glTranslatef(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT/2.0f, 0.0f);
	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f( 0.0f,  0.0);
		glVertex2f( 0.0f, 10.0f);
		glVertex2f(10.0f, 10.0f);
		glVertex2f(10.0f,  0.0f);
	glEnd();

	// update screen
	glutSwapBuffers();
}

void handlekeys(unsigned char key, int x, int y)
{
	if (key =='w') {
		cameray -= 16.0f;	
	}
	else if (key == 's') {
		cameray += 16.0f;
	}
	else if (key == 'a') {
		camerax -= 16.0f;
	}
	else if (key == 'd') {
		camerax += 16.0f;
	}

	printf("camerax = %.2f, cameray = %.2f\n", camerax, cameray);

	// take matrix off stack and reset it
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glLoadIdentity();

	// move camera
	glTranslatef( -camerax, -cameray, 0.0f);
	
	// save default matrix again with camera translations
	glPushMatrix();
}
