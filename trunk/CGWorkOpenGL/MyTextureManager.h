#pragma once

#include <string>
#include "PngWrapper.h"
#include "MyMaterialManager.h"

using std::string;

//
class MyTextureManager
{
public:
	MyTextureManager(void);
	~MyTextureManager(void);

	void addPTexture(const char *str, bool fullPath, bool mipmap = false);
	void setupTextureParams(MyMaterialManager& materialManager);
	void set();
	void enable(bool enable);
	const char* getTextureFile(void) { return m_textureFile.c_str(); }

	/** m_textureDir points to the directory to search for texture files in. This defaults
		to the current working directory. Assign a different path to this field if you
		want to change the search path.
	**/
	static std::string m_textureDir;

private:
	void bindTexture(PngWrapper* wrapper, int level = 0);
	
private:
	int m_sWidth, m_sHeight;
	string m_textureFile;
	unsigned int m_texture;
	bool m_showTexture;
	bool m_enabled;
	bool m_isAuto;
	unsigned char* m_checkImage[64];	// we support up-to 64 levels of mipmapping
	unsigned char* m_sImage[64];
	MyMaterialManager m_materialManager;
	bool m_mipmapMode;
	
// Find the largest power of two that is
// less than or equal to the value
	int nearestPower( int value );
};
