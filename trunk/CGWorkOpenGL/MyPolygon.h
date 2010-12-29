#pragma once
#include "mygldrawable.h"
#include "myvertex.h"
#include "PngWrapper.h"


class MyPolygon : public MyGlDrawable
{
public:
	MyPolygon(int nVertices, int norm_x = 0, int norm_y = 0, int norm_z = 0);
	~MyPolygon(void);
	void AddVertex(MyVertex& v);
	void Draw(void);

	MyVertex *m_vertices;	// vertices array
	MyVector normal;
	double c_x, c_y, c_z;	// center-point of polygon

	// you can specify normal length to draw implicitly or let it be calculated relative to
	// the size of the face
	void DrawNormals(bool faceNormal, bool vertexNormals, double size = 0);
	
	void drawTesselated(GLUtesselator* tobj);


private:
	int nextVertex;	// points to first unused index in vertex array
	bool normalInitialized;	// is normal given in constructor or to be calculated?
};
