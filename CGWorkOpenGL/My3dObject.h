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
	void DrawNormals(bool faceNormals, bool vertexNormals);

	void addPTexture(const char *str, bool fullPath);

	/* get a display-list index for the list that draws the requested normals. a */
	int GetNormalsDisplayList(bool faceNormals, bool vertexNormals, bool recompile = false);
	void PushPostEffect(MyPostEffect* fx, long flags = 0);
	void PopPostEffect();

	MyPolygon **m_polygons;
	double m_color[3],
		   m_transp;

	static const int PFX_VERTICES	= 0x1;
	static const int PFX_FACES		= 0x2;

private:


private:
	int nextPoly;
	int arrSize;
	int m_NormalsDisplayList[4];	// holds a display list for each of the 4 possible combinations
									// of normal-drawing settings (off/off, on/off etc...)
	bool m_showTexture;
	GLuint m_textureName;
	MyTextureManager m_textureManager;
};
