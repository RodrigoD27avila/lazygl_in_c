#include <stdio.h>
#include <stdlib.h>

#include "util.h"

int gviewportmode = VIEW_PORT_MODE_FULL;

static void FullView();
static void HalfCenterView();
static void HalfTopView();
static void QuadView();
static void RadarView();

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

	switch (gviewportmode) {
	default:
	case VIEW_PORT_MODE_FULL:
		FullView();
		break;
	case VIEW_PORT_MODE_HALF_CENTER:
		HalfCenterView();
		break;
	case VIEW_PORT_MODE_HALF_TOP:
		HalfTopView();
		break;
	case VIEW_PORT_MODE_QUAD:
		QuadView();
		break;
	case VIEW_PORT_MODE_RADAR:
		RadarView();
		break;
	}

	// update screen
	glutSwapBuffers();
}

void handlekeys(unsigned char key, int x, int y)
{
	if (key =='q') {
		
		gviewportmode = (gviewportmode == VIEW_PORT_MODE_RADAR)
			? VIEW_PORT_MODE_FULL
			: gviewportmode + 1;
	}
}

static void FullView()
{
	// fill screen
	glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	// red quad
	glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex2f(-SCREEN_WIDTH / 2.0f, -SCREEN_HEIGHT / 2.0f);
		glVertex2f( SCREEN_WIDTH / 2.0f, -SCREEN_HEIGHT / 2.0f);
		glVertex2f( SCREEN_WIDTH / 2.0f,  SCREEN_HEIGHT / 2.0f);
		glVertex2f(-SCREEN_WIDTH / 2.0f,  SCREEN_HEIGHT / 2.0f);
	glEnd();
}

static void HalfCenterView()
{
	// center view port
	glViewport(SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 4.0f,
		SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);

	glBegin(GL_QUADS);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(-SCREEN_WIDTH / 2.0f, -SCREEN_HEIGHT / 2.0f);
		glVertex2f( SCREEN_WIDTH / 2.0f, -SCREEN_HEIGHT / 2.0f);
		glVertex2f( SCREEN_WIDTH / 2.0f,  SCREEN_HEIGHT / 2.0f);
		glVertex2f(-SCREEN_WIDTH / 2.0f,  SCREEN_HEIGHT / 2.0f);
	glEnd();
}

static void HalfTopView()
{
	// view at top
	glViewport(SCREEN_WIDTH /4.0f, SCREEN_HEIGHT / 2.0f,
		SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT/ 2.0f);
	
	glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(-SCREEN_WIDTH / 2.0f, -SCREEN_HEIGHT / 2.0f);
		glVertex2f( SCREEN_WIDTH / 2.0f, -SCREEN_HEIGHT / 2.0f);
		glVertex2f( SCREEN_WIDTH / 2.0f,  SCREEN_HEIGHT / 2.0f);
		glVertex2f(-SCREEN_WIDTH / 2.0f,  SCREEN_HEIGHT / 2.0f);
	glEnd();
}

static void DrawQuads(GLfloat r, GLfloat g, GLfloat b)
{
	glBegin(GL_QUADS);
		glColor3f(r, g, b);
		glVertex2f(-SCREEN_WIDTH / 4.0f, -SCREEN_HEIGHT / 4.0f);
		glVertex2f( SCREEN_WIDTH / 4.0f, -SCREEN_HEIGHT / 4.0f);
		glVertex2f( SCREEN_WIDTH / 4.0f,  SCREEN_HEIGHT / 4.0f);
		glVertex2f(-SCREEN_WIDTH / 4.0f,  SCREEN_HEIGHT / 4.0f);
	glEnd();
}

static void QuadView()
{
	glViewport(0.0f, 0.0f,
		SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
	DrawQuads(1.0f, 0.0f, 0.0f);

	glViewport(SCREEN_WIDTH / 2.0f, 0.0f,
		SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
	DrawQuads(0.0f, 1.0f, 0.0f);

	glViewport(0.0f, SCREEN_HEIGHT / 2.0f,
		SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
	DrawQuads(0.0f, 0.0f, 1.0f);

	glViewport(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f,
		SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
	DrawQuads(1.0f, 1.0f, 0.0f);

	
}

static void DrawRadar(GLfloat r1, GLfloat g1, GLfloat b1,
		GLfloat r2, GLfloat g2, GLfloat b2)
{
	glBegin(GL_QUADS);
		glColor3f(r1, g1, b1);
		glVertex2f(-SCREEN_WIDTH / 8.0f, -SCREEN_HEIGHT / 8.0f);
		glVertex2f( SCREEN_WIDTH / 8.0f, -SCREEN_HEIGHT / 8.0f);
		glVertex2f( SCREEN_WIDTH / 8.0f,  SCREEN_HEIGHT / 8.0f);
		glVertex2f(-SCREEN_WIDTH / 8.0f,  SCREEN_HEIGHT / 8.0f);
		glColor3f(r2, g2, b2);
		glVertex2f(-SCREEN_WIDTH / 16.0f, -SCREEN_HEIGHT / 16.0f);
		glVertex2f( SCREEN_WIDTH / 16.0f, -SCREEN_HEIGHT / 16.0f);
		glVertex2f( SCREEN_WIDTH / 16.0f,  SCREEN_HEIGHT / 16.0f);
		glVertex2f(-SCREEN_WIDTH / 16.0f,  SCREEN_HEIGHT / 16.0f);
	glEnd();	
}

static void RadarView()
{
	glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
	DrawRadar(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	
	glViewport(SCREEN_WIDTH / 2.0f , SCREEN_HEIGHT / 2.0f,
		 SCREEN_WIDTH / 2.0f , SCREEN_HEIGHT / 2.0f );
	DrawRadar(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
}
