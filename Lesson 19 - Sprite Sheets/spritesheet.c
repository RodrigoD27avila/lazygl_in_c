#include "spritesheet.h"
#include "vertexdata2d.h"

void spriteSheetAddClip(struct SpriteSheet *ssh, int pos,
		struct Rect *rect)
{
	struct Rect *myrect = spriteSheetgetClip(ssh, pos);
	myrect->x = rect->x;
	myrect->y = rect->y;
	myrect->w = rect->w;
	myrect->h = rect->h;
}


Rect *spriteSheetgetClip(struct SpriteSheet *ssh, int pos)
{
	return &ssh->clips[pos];
}

void spriteSheetGenerateDataBuffer(struct SpriteSheet *ssh, int size)
{
	if (sst.tex.id == 0) {
		return;
	}

	struct VertexData2D vdata =
		 malloc((sizeof(struct VertexData2D) * size) * 4);

	// allocate vertex data buffer
	glgenBuffers(1, &ssh->vbuffer);

	// allocate index buffer names
	glGenBuffers(size, &ssh->ibuffer);

	// go through clips
	GLfloat tw = ssh.tex.w;
	GLfloat th = ssh.tex.h;
	GLuint indices = {0, 0, 0, 0};

	int i;
	for (i=0; i<size; i++) {
		// intialize indices
		indices[0] = i * 4 + 0;
		indices[1] = i * 4 + 1;
		indices[2] = i * 4 + 2;
		indices[3] = i * 4 + 3;

	

			
	}
	

	
}

void spriteSheetFree(struct SpriteSheet *ssh)
{
}

void spriteSheetRender(struct SpriteSheet *ssh, int pos)
{
}

