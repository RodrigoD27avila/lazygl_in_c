#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include "opengl.h"

struct Texture {
	GLuint id;
	GLuint w, h;
};

void textureLoadFromPixel32(struct Texture *tex, GLuint *pixels,
		GLuint w, GLuint h);

void textureLoadFromFile(struct Texture *tex, const char *filename);

void textureFree(struct Texture *tex);

void textureRender(struct Texture *tex, GLfloat x, GLfloat y,
	struct Rect *clip);

#endif /* TEXTURE_H_INCLUDED */
