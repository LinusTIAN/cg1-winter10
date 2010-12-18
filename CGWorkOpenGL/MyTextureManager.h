#pragma once

#include "PngWrapper.h"
//
class MyTextureManager
{
public:
	MyTextureManager(void);
	~MyTextureManager(void);


	int addPTexture(const char *str, bool fullPath);

private:
	int setUpTexture(PngWrapper* wrapper);
	
	
// Find the largest power of two that is
// less than or equal to the value
	int nearestPower( int value );
};
