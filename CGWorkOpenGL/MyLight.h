#pragma once


//#include "gl\gl.h"    // Include the standard OpenGL  headers
//#include "gl\glu.h"   // Add the utility library

#include "Light.h"


class MyLight
{
public:
	MyLight(void);
	~MyLight(void);

	void setupGeneralLight(bool show, LightParams& params );
	void showLight(LightParams& light, int num);

private:
	LightParams m_params ;
};
