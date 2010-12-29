#pragma once

#include "PngWrapper.h"
#include "MyMaterialManager.h"
//
class MyTextureManager
{
public:
	MyTextureManager(void);
	~MyTextureManager(void);

	void addPTexture(const char *str, bool fullPath);
	void setupTextureParams(MyMaterialManager& materialManager);
	void set();
	void enable(bool enable);

private:
	void bindTexture(PngWrapper* wrapper);
	
private:
	int m_sWidth, m_sHeight;
	unsigned int m_texture;
	unsigned char* m_sImage;
	bool m_showTexture;
	bool m_enabled;
	MyMaterialManager m_materialManager;
	
	
// Find the largest power of two that is
// less than or equal to the value
	int nearestPower( int value );
};
