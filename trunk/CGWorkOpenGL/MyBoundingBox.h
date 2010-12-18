#pragma once

#include <cmath>
#include <windows.h>

class MyBoundingBox
{
public:
	MyBoundingBox()
	{
		x_min = x_max = y_min = y_max = z_min = z_max = 0;
		initialized = false;
	}

	MyBoundingBox(double x_min, double x_max,
				  double y_min, double y_max,
				  double z_min, double z_max)
		:	x_min(x_min), x_max(x_max),
			y_min(y_min), y_max(y_max),
			z_min(z_min), z_max(z_max)
	{
		initialized = true;
	}

	double	x_min, x_max,
			y_min, y_max,
			z_min, z_max;

	bool initialized;

	void update(MyBoundingBox b){
		if (!initialized){
			x_min = b.x_min; x_max = b.x_max;
			y_min = b.y_min; y_max = b.y_max;
			z_min = b.z_min; z_max = b.z_max;
			initialized = true;
		}
	
		x_min = min(x_min, b.x_min); x_max = max(x_max, b.x_max);
		y_min = min(y_min, b.y_min); y_max = max(y_max, b.y_max);
		z_min = min(z_min, b.z_min); z_max = max(z_max, b.z_max);
	}

	void update(double x, double y, double z){
		if (!initialized){
			x_min = x; x_max = x;
			y_min = y; y_max = y;
			z_min = y; z_max = y;
			initialized = true;
		}
	
		x_min = min(x_min, x); x_max = max(x_max, x);
		y_min = min(y_min, y); y_max = max(y_max, y);
		z_min = min(z_min, z); z_max = max(z_max, z);
	}

	double xSize(void)
	{
		return std::abs(x_max - x_min);
	}

	double ySize(void)
	{
		return std::abs(y_max - y_min);
	}

	double zSize(void)
	{
		return std::abs(z_max - z_min);
	}

	double GetCenterX(void)
	{
		return (x_max + x_min)/2;
	}

	double GetCenterY(void)
	{
		return (y_max + y_min)/2;
	}

	double GetCenterZ(void)
	{
		return (z_max + z_min)/2;
	}
};
