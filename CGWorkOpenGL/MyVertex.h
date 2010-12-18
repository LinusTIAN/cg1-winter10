#pragma once
#include "mygldrawable.h"
#include "MyVector.h"
#include <windows.h>
#include "gl\gl.h"    // Include the standard OpenGL  headers
#include "gl\glu.h"   // Add the utility library

class MyVertex :
	public MyGlDrawable
{
public:
	MyVertex(void);
	MyVertex(double x, double y, double z);
	MyVertex(double x, double y, double z,
			 double norm_x, double norm_y, double norm_z);
	~MyVertex(void);

	void Draw(void) {
		glBegin(GL_POINTS);
			glVertex3d(x, y, z);
		glEnd();
	}

	MyBoundingBox GetBoundingBox()
	{
		return MyBoundingBox(x,x,y,y,z,z);
	}

	double x, y, z;
	MyVector normal;
};
