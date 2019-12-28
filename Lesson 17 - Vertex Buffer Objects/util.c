#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "texture.h"
#include "rect.h"
#include "vertex2d.h"

static struct Vertex2D vertices[4];
static GLuint indices[4];
static GLuint vbuffer;
static GLuint ibuffer;

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

	// set rendering indices
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;

	// create VBO
	glGenBuffers(1, &vbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(struct Vertex2D),
		vertices, GL_STATIC_DRAW);

	// create IBO
	glGenBuffers(1, &ibuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint),
		indices, GL_STATIC_DRAW);
	
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

		// set vertex data
		glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
		glVertexPointer(2, GL_FLOAT, 0, NULL);

		// draw quad using vertex data and index data
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuffer);
		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, NULL);

	glDisableClientState(GL_VERTEX_ARRAY);

	// update screen
	glutSwapBuffers();
}

void handlekeys(unsigned char key, int x, int y)
{
	if (key =='q') {
	}
}
