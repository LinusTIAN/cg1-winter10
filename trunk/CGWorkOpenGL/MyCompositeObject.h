#pragma once
#include "My3dObject.h"

class MyCompositeObject: public MyGlDrawable
{
public:
	/** Selector for Draw(...). Meanings:
		SELECT_OPAQUE - Draw only completely opaque objects
		SELECT_TRANSPARENT - Draw only partially transparent objects (alpha =/= 1)
		SELECT_ALL - Draw all objects (logical OR of SELECT_OPAQUE and SELECT_TRANSPARENT)
	**/
	enum OBJECT_SELECTOR_T {SELECT_OPAQUE = 0x1, SELECT_TRANSPARENT = 0x2, SELECT_ALL = 0x3};

	MyCompositeObject(void);
	~MyCompositeObject(void);
	/* only use addObjectRef to store a pointer to an allocated My3dObjcet. DO NOT DELETE THIS
	   POINTER YOURSELF! THE CLASS NEEDS IT AND WILL TAKE CARE OF DELETING IT ON DESTRUCTION */
	void addObjectRef(My3dObject* obj);
	/** This overridden method allows you, in addition to the regular Draw behavior of
		glDrawable objects, to select what sub-objects to draw. See the definition of
		OBJECT_SELECTOR_T for possible values. The default behavior if no value is
		specified is to draw all sub-objects.
	**/
	void Draw() { this->Draw(SELECT_ALL); }
	void Draw(OBJECT_SELECTOR_T to_draw);

	/** This overridden method allows you, in addition to the regular GetDisplayList behavior of
		glDrawable objects, to select what sub-objects this display list will draw. See the
		definition of OBJECT_SELECTOR_T for possible values. The default behavior if no value is
		specified is to draw all sub-objects.
	**/
	int GetDisplayList(bool recompile = false) { 
		return this->GetDisplayList(SELECT_ALL, recompile); 
	}
	int GetDisplayList(OBJECT_SELECTOR_T to_draw, bool recompile = false);

	void recompileAll(void);

	void changeColor(double r, double g, double b);
	void DrawNormals(bool faceNormals, bool vertexNormals);
	/* get a display-list index for the list that draws the requested normals */
	int GetNormalsDisplayList(bool faceNormals, bool vertexNormals, bool recompile = false);

	My3dObject **m_objects;
	int m_nextObj;
	int m_arrSize;

protected:
	int m_NormalsDisplayList[4];	// holds a display list for each of the 4 possible combinations
									// of normal-drawing settings (off/off, on/off etc...
	int m_compDisplayLists[3];		// holds a display list for each of the 3 possible combinations
									// of drawing settings (transparent, opaque, both)


	int temp;
};
