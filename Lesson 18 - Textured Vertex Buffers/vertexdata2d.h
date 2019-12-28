#ifndef VERTEXDATA2D_H_INCLUDED
#define VERTEXDATA2D_H_INCLUDED

#include "vertex2d.h"
#include "texcoord.h"

struct VertexData2D {
	struct Vertex2D pos;
	struct TexCoord coord;
};

#endif //VERTEXDATA2D_H_INCLUDED
