#pragma once

#include "MyGlDrawable.h"

// Defines a custom post-effect to be applied to a GlDrawable object immediately
// before it is output to the screen. You can subclass this to implement any
// kind of post-effect you desire by overriding the Apply() method.
class MyPostEffect
{
public:
	MyPostEffect(void) {}
	virtual ~MyPostEffect(void) {}

	// apply post effect to target GlDrawable
	virtual void Apply(MyGlDrawable& target) = 0;
};
