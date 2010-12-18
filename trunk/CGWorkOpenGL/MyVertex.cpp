#include "MyVertex.h"

MyVertex::MyVertex(void)
	:	x(0), y(0), z(0),
		normal(0, 0, 0)
{
}

MyVertex::MyVertex(double x, double y, double z)
	:	x(x), y(y), z(z),
		normal(0, 0, 0)
{
}

MyVertex::MyVertex(double x, double y, double z, double norm_x, double norm_y, double norm_z)
	:	x(x), y(y), z(z),
		normal(norm_x, norm_y, norm_z)
{
	normal /= normal.Size();	// normalize to unit vector
}

MyVertex::~MyVertex(void)
{
}
