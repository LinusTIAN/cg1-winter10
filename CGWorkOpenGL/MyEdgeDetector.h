#pragma once

#include "stdafx.h"
#include "shadersSkel.h"

class MyEdgeDetector
{
public:
	MyEdgeDetector(int screen_w, int screen_h);
	~MyEdgeDetector(void);
	void detectEdges();
	void drawEdges();
	void stencilEdges();
	GLubyte* getEdgeMap();

private:
	int w, h;
	GLfloat *read_buffer;
	GLubyte	*write_buffer;

	void readBuffers();
};
