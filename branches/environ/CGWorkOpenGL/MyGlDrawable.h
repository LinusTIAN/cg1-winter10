#pragma once

#include "MyBoundingBox.h"
#include <list>

class MyGlDrawable
{
public:
	MyGlDrawable(void);
	virtual ~MyGlDrawable(void);

	virtual void Draw(void) = 0;
	// set recompile to True if you want the display list to be recompiled even if it has been
	// previously created
	virtual int GetDisplayList(bool recompile = false);
	/**	Causes all display lists stored in the object to be recompiled.
		This is relevant mainly for objects which can generate more than a single display
		list, to make sure all of the lists are up-to-date.
	**/
	virtual void recompileAll(void) { GetDisplayList(true); }
	virtual void DrawBoundingBox(void);

	MyBoundingBox bbox;

protected:
	int m_displayList;
};