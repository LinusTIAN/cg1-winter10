#pragma once

#include "mygldrawable.h"
#include "mypolygon.h"
#include "MyTextureManager.h"

class My3dObject :
	public MyGlDrawable
{
public:
	My3dObject(int nPolygons = 20);
	~My3dObject(void);
	/* only use AddPolyPtr to store a pointer to an allocated MyPolygon. DO NOT DELETE THIS
	   POINTER YOURSELF! THE CLASS NEEDS IT AND WILL TAKE CARE OF DELETING IT ON DESTRUCTION */
	void AddPolyRef(MyPolygon* p);
	void Draw(void);
	void DrawNormals(bool faceNormals, bool vertexNormals, double normSize = 0);
	/* get a display-list index for the list that draws the requested normals */
	int GetNormalsDisplayList(bool faceNormals, bool vertexNormals, double normSize = 0, bool recompile = false);

	void addPTexture(const char *str, bool fullPath);
	void enableTexture(bool enable);

	MyPolygon **m_polygons;
	double m_color[3],
		   m_alpha;
	MyTextureManager m_textureManager;

private:
	int nextPoly;
	int arrSize;
	int m_NormalsDisplayList[4];	// holds a display list for each of the 4 possible combinations
									// of normal-drawing settings (off/off, on/off etc...
};