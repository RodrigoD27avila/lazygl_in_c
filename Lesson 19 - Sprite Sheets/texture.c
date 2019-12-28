#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <IL/il.h>
#include <IL/ilu.h>

#include "texture.h"
#include "rect.h"
#include "vertexdata2d.h"

void textureLoadFromFile(struct Texture *tex, const char *filename)
{
	ILuint id = 0;
	ilGenImages(1, &id);
	ilBindImage(id);

	ILboolean success = ilLoadImage(filename);
	if(!success) {
		fprintf(stderr, "Unable to load texture: %s\n",
			filename);
		exit(EXIT_FAILURE);
	}

	success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	if(!success) {
		fprintf(stderr, "Unable to convert texture.\n");
		exit(EXIT_FAILURE);
	}

	// load 
	textureLoadFromPixel32(tex, (GLuint *)ilGetData(),
		(GLuint)ilGetInteger(IL_IMAGE_WIDTH),
		(GLuint)ilGetInteger(IL_IMAGE_HEIGHT));

	ilDeleteImages(1, &id);
}

void textureLoadFromPixel32(struct Texture *tex, GLuint *pixels,
		GLuint w, GLuint h)
{
	// free previous texture
	textureFree(tex);

	// set width and height
	tex->w = w;
	tex->h = h;

	// generate id
	glGenTextures(1, &tex->id);
	
	// bind texture
	glBindTexture(GL_TEXTURE_2D, tex->id);

	// generate texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h,
		0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	// set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	// unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	// check for errors
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		fprintf(stderr, "error loading texture: %s\n",
			gluErrorString(error));
		exit(EXIT_FAILURE);
	}

	// initialize vbo
	textureInitVBO(tex);
}

void textureFree(struct Texture *tex)
{
	if (tex->id == 0) {
		return;
	}

	glDeleteTextures(1, &tex->id);
	tex->id = 0;
	tex->w  = 0;
	tex->h  = 0;

	textureFreeVBO(tex);
}

void textureRender(struct Texture *tex, GLfloat x, GLfloat y, struct Rect *clip)
{
	if (tex->id == 0) {
		return;
	}

	// texture coordinates
	struct Rect texcoord = {0.0f, 0.0f, 1.0f, 1.0f};
	
	// vertex coordinates
	struct Rect vercood = {0.0f, 0.0f, (double)tex->w, (double)tex->h};

	// handle clipping
	if (clip != NULL) {
		// texture coordinates
		texcoord.x = (double) (clip->x / tex->w );
		texcoord.y = (double) (clip->y / tex->h );
		texcoord.w = (double)((clip->x + clip->w) / tex->w);
		texcoord.h = (double)((clip->y + clip->h) / tex->h);
	
		// vertex coordinates
		vercood.w = clip->w;
		vercood.h = clip->h;
	}

	// move to render point
	glTranslatef(x , y , 0.0f);

	// set texture id
	glBindTexture(GL_TEXTURE_2D, tex->id);

	// set vertex data
	struct VertexData2D vdata[4];

	vdata[0].coord.s = texcoord.x;
	vdata[0].coord.t = texcoord.y;
	
	vdata[1].coord.s = texcoord.w;
	vdata[1].coord.t = texcoord.y;
	
	vdata[2].coord.s = texcoord.w;
	vdata[2].coord.t = texcoord.h;
	
	vdata[3].coord.s = texcoord.x;
	vdata[3].coord.t = texcoord.h;

	// set vertex positions
	vdata[0].pos.x = vercood.x;
	vdata[0].pos.y = vercood.y;
	
	vdata[1].pos.x = vercood.w;
	vdata[1].pos.y = vercood.y;

	vdata[2].pos.x = vercood.w;
	vdata[2].pos.y = vercood.h;

	vdata[3].pos.x = vercood.x;
	vdata[3].pos.y = vercood.h;

	// set texture id
	glBindTexture(GL_TEXTURE_2D, tex->id);
	
	// enable vertex and texture coordinates arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	// bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, tex->vboid);

	// update vertex buffer data
	glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * sizeof(struct VertexData2D),
		vdata);

	// set texture coordinate data
	glTexCoordPointer(2, GL_FLOAT, sizeof(struct VertexData2D),
		(GLvoid *)offsetof(struct VertexData2D, coord));
	
	// set vertex data
	glVertexPointer(2, GL_FLOAT, sizeof(struct VertexData2D),
		(GLvoid *)offsetof(struct VertexData2D, pos));

	// draw quad using vertex data and index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tex->iboid);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, NULL);

	// disable	
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}


void textureInitVBO(struct Texture *tex)
{
	if (tex->id  == 0 && tex->vboid != 0) {
		return;
	}

	// vertex data
	struct VertexData2D vdata[4];
	memset(vdata, 0, sizeof(struct VertexData2D));
	GLuint              idata[4]  = {0,1,2,3};

	// create vbo
	glGenBuffers(1, &tex->vboid);
	glBindBuffer(GL_ARRAY_BUFFER, tex->vboid);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(struct VertexData2D),
		vdata, GL_DYNAMIC_DRAW);

	// create ibo
	glGenBuffers(1, &tex->iboid);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tex->iboid);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint),
		idata, GL_DYNAMIC_DRAW);

	// unbind buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void textureFreeVBO(struct Texture *tex)
{
	if (tex->vboid == 0) {
		return;
	}

	glDeleteBuffers(1, &tex->vboid);
	glDeleteBuffers(1, &tex->iboid);

	tex->vboid = 0;
	tex->iboid = 0;
}
