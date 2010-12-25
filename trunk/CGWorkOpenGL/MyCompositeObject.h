#pragma once
#include "My3dObject.h"

class MyCompositeObject: public MyGlDrawable
{
public:
	MyCompositeObject(void);
	~MyCompositeObject(void);
	/* only use addObjectRef to store a pointer to an allocated My3dObjcet. DO NOT DELETE THIS
	   POINTER YOURSELF! THE CLASS NEEDS IT AND WILL TAKE CARE OF DELETING IT ON DESTRUCTION */
	void addObjectRef(My3dObject* obj);
	void Draw(void);
	void changeColor(double r, double g, double b);
	void DrawNormals(bool faceNormals, bool vertexNormals);
	/* get a display-list index for the list that draws the requested normals */
	int GetNormalsDisplayList(bool faceNormals, bool vertexNormals, bool recompile = false);

	My3dObject **m_objects;
	int m_nextObj;
	int m_arrSize;

private:
	int m_NormalsDisplayList[4];	// holds a display list for each of the 4 possible combinations
									// of normal-drawing settings (off/off, on/off etc...
};
