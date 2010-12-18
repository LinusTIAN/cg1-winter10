#pragma once

#include "MyBoundingBox.h"
#include <list>

class MyPostEffect;	// forward declaration

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

	// add a post-effect to the list of effects to execute before an object is drawn
	// to the screen. flags is undefined and can be used for your own purposes
	virtual void PushPostEffect(MyPostEffect* fx, long flags = 0);
	// pop the earliest added post-effect (push-pop is performed in a FIFO order)
	virtual void PopPostEffect(void);

	MyBoundingBox bbox;

protected:
	int m_displayList;
	std::list<MyPostEffect*> postEffects;
};