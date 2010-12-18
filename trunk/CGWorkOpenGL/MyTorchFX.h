#pragma once
#include "myposteffect.h"
#include "globals.h"

class MyTorchFX :
	public MyPostEffect
{
public:
	MyTorchFX(double range = 1.0): R(1.0), G(1.0), B(1.0), dim_range(range) { TransformsUpdated(); }
	~MyTorchFX(void) {}
	void Apply(MyGlDrawable& target);
	// call this when the transformation matrix is updated and before any subsequent call to Apply
	// can be made
	void TransformsUpdated(void);

	double R, G, B;
	double dim_range;
	int cursor_x, cursor_y, cursor_z;

private:
	double	modelMatrix[16],
			projMatrix[16];
	int viewportMatrix[4];
};
