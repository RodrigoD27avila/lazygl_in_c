#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "texture.h"
#include "rect.h"
#include "vertex2d.h"

struct Vertex2D vertices[4];

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

	//glEnable(GL_BLEND);
	//glDisable(GL_DEPTH_TEST);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
	// set quad vertices
	vertices[0].x = SCREEN_WIDTH  * (1.0f / 4.0f);
	vertices[0].y = SCREEN_HEIGHT * (1.0f / 4.0f);
	vertices[1].x = SCREEN_WIDTH  * (3.0f / 4.0f);
	vertices[1].y = SCREEN_HEIGHT * (1.0f / 4.0f);
	vertices[2].x = SCREEN_WIDTH  * (3.0f / 4.0f);
	vertices[2].y = SCREEN_HEIGHT * (3.0f / 4.0f);
	vertices[3].x = SCREEN_WIDTH  * (1.0f / 4.0f);
	vertices[3].y = SCREEN_HEIGHT * (3.0f / 4.0f);
	
	int i;
	for (i=0; i<4;i++) {
		printf("x = %.2f, y = %.2f\n", vertices[i].x,
			vertices[i].y);
	}
}

void update()
{
}

void render()
{
	// clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	// enable vertex arrays
	glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, vertices);
		glDrawArrays(GL_QUADS, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);

	// update screen
	glutSwapBuffers();
}

void handlekeys(unsigned char key, int x, int y)
{
	if (key =='q') {
	}
}
