#pragma once

#include "PngWrapper.h"
#include "MyMaterialManager.h"
//
class MyTextureManager
{
public:
	MyTextureManager(void);
	~MyTextureManager(void);


	int addPTexture(const char *str, bool fullPath);
	void setupTexture(MyMaterialManager& materialManager);

private:
	int bindTexture(PngWrapper* wrapper);
	
	
// Find the largest power of two that is
// less than or equal to the value
	int nearestPower( int value );
};
