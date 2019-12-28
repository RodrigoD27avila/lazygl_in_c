#ifndef SPRITESHEET_H_INCLUDED
#define SPRITESHEET_H_INCLUDED

#include "opengl.h"
#include "texture.h"
#include "rect.h"

#define MAX_SPRITES 8

struct SpriteSheet {
	struct Texture tex;
	struct Rect    clips[MAX_SPRITES];
	GLuint         vbuffer;
	GLuint         ibuffer[MAX_SPRITES];
};

void spriteSheetAddClip(struct SpriteSheet *ssh, int pos,
		struct Rect *rect);

Rect *spriteSheetgetClip(struct SpriteSheet *ssh, int pos);

void spriteSheetGenerateDataBuffer(struct SpriteSheet *ssh, int size);

void spriteSheetFree(struct SpriteSheet *ssh);

void spriteSheetRender(struct SpriteSheet *ssh, int pos);

#endif //SPRITESHEET_H_INCLUDED
