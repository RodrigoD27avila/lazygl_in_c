#include <stdio.h>
#include <stdlib.h>

#include "util.h"

static GLfloat vx;
static GLfloat vy;
static GLfloat vw = SCREEN_WIDTH;
static GLfloat vh = SCREEN_HEIGHT;

static void DrawRect(GLfloat x, GLfloat y, GLfloat w, GLfloat h)
{
	glBegin(GL_QUADS);
		glVertex2f(x  , y  );
		glVertex2f(x  , y+h);
		glVertex2f(x+w, y+h);
		glVertex2f(x+w, y  );
	glEnd();	
}

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

	glViewport(0, SCREEN_HEIGHT - 200, 200, 200);
	glColor3f(1.0f, 0.0f, 1.0f);
	DrawRect(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);

	// update screen
	glutSwapBuffers();
}

void handlekeys(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q' : vx += 5.0f; break;
	case 'Q' : vx -= 5.0f; break;
	case 'w' : vy += 5.0f; break;
	case 'W' : vy -= 5.0f; break;
	case 'e' : vw += 5.0f; break;
	case 'E' : vw -= 5.0f; break;
	case 'r' : vh += 5.0f; break;
	case 'R' : vh -= 5.0f; break;
	case 'z' :
		vx = 0.0f; vy = 0.0f;
		vw = SCREEN_WIDTH;
		vh = SCREEN_HEIGHT;
	break;
	case 's':
		float r = (float)rand() / (float)RAND_MAX;
		float g = (float)rand() / (float)RAND_MAX;
		float b = (float)rand() / (float)RAND_MAX;

		glColor3f(r, g, b);
		DrawRect(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT,
			 rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT);
		break;

		
	}

	printf ("glViewport(%2.0f, %2.0f, %2.0f, %2.0f);\n",
		vx, vy, vw, vh);
	// update screen
	glutSwapBuffers();
}
