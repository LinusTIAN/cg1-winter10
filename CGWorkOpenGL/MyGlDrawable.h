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
	virtual void DrawBoundingBox(void);

	MyBoundingBox bbox;

protected:
	int m_displayList;
};