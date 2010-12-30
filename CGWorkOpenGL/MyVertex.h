#pragma once
#include "mygldrawable.h"
#include "MyVector.h"
#include <windows.h>
#include "gl\gl.h"    // Include the standard OpenGL  headers
#include "gl\glu.h"   // Add the utility library

class MyVertex : public MyGlDrawable
{
public:
	MyVertex(void);
	MyVertex(double x, double y, double z);
	~MyVertex(void);

	void setUV(double u, double v);
	void setNormal(double norm_x, double norm_y, double norm_z);

	void Draw();


public:
	double x, y, z;
	MyVector normal;

	double m_u, m_v;
	bool m_hasUV;
};
