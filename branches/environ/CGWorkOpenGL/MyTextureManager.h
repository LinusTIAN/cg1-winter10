#pragma once

#include <string>
#include "PngWrapper.h"
#include "MyMaterialManager.h"

using std::string;

class MyTextureManager
{
public:
	MyTextureManager(void);
	~MyTextureManager(void);

	void addPTexture(const char *str, bool fullPath);
	void setupTextureParams(MyMaterialManager& materialManager);
	void bindTexture(PngWrapper* wrapper);
	void set();
	void enable(bool enable);

	/** m_textureDir points to the directory to search for texture files in. This defaults
		to the current working directory. Assign a different path to this field if you
		want to change the search path.
	**/
	static string m_textureDir;

private:
	int m_sWidth, m_sHeight;
	unsigned int m_texture;
	unsigned char* m_sImage;
	bool m_showTexture;
	bool m_enabled;
	bool m_isAuto;
	unsigned char* m_checkImage;
	MyMaterialManager m_materialManager;
	string m_picFile;
	bool m_enableMipMap;
	
// Find the largest power of two that is
// less than or equal to the value
	int nearestPower( int value );
};
