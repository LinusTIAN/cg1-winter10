#include "MyTextureManager.h"
#include "stdafx.h"

#include "globals.h"
#include <new>
#include <cstring>
#include <string>
#include <assert.h>

using namespace std;


string MyTextureManager::m_textureDir = ".";


MyTextureManager::MyTextureManager(void)
{
	m_enabled = true;
	m_showTexture = false;
	for (int i = 0; i < 64; i++)
		m_checkImage[i] = NULL;
	m_isAuto = true;
	m_textureFile = "";
	m_mipmapMode = false;
}

MyTextureManager::~MyTextureManager(void)
{
	if (m_checkImage[0] != NULL){
		glDeleteTextures(1,&m_texture);
		//delete m_checkImage;
	}
}

int MyTextureManager::nearestPower( int value )
{
    int i = 1;

    if (value == 0) return -1;      /* Error! */
    for (;;) {
         if (value == 1) return i;
         else if (value == 3) return i*4;
         value >>= 1; i *= 2;
    }
}


void MyTextureManager::addPTexture(const char *str, bool fullPath, bool mipmap){
	
	string s(str);
	string fileName(str);
	if (! fullPath){
		int length = s.find_first_of(',');
		fileName = s.substr(0,length);
		//s = s.substr(length+1,s.size());
		//
		//length = s.find_first_of(',');
		//string val1 = s.substr(0,length);
		//s = s.substr(length+1,s.size());
		//
		//length = s.find_first_of(',');
		//string val2 = s.substr(0,length);
		//s = s.substr(length+1,s.size());
		//
		//length = s.find_first_of(',');
		//string val3 = s.substr(0,length);

		fileName = fileName.substr(0,fileName.size()-3);
		fileName = MyTextureManager::m_textureDir + "\\" + fileName+ "png";
	}

	m_textureFile = fileName;

	if (!mipmap)
	{
		// setup a regular texture
		PngWrapper wrapper;
		wrapper.SetFileName(fileName.c_str());
		if (!wrapper.ReadPng()){
			AfxMessageBox("Texture file can not be read");
			return ;
		}
		bindTexture(&wrapper);
	} else
	{
		// setup a mip-mapped texture
		m_mipmapMode = true;
		PngWrapper wrapper;

		for (	int i = 0;
				wrapper.GetHeight() != 1 || wrapper.GetWidth() != 1;
				i++		) {
			fileName.replace(fileName.length() - 5, 5, string(1, 'a'+i) + ".png");	// generate filename for next mipmaps
			wrapper.SetFileName( fileName.c_str() );
			if (!wrapper.ReadPng()) {
				AfxMessageBox("Texture file can not be read");
				return;
			}
			bindTexture(&wrapper, i);
		}
	}

	m_showTexture = true;
}


void MyTextureManager::bindTexture(PngWrapper* wrapper, int level) {
	
	// Read the texture image
	int imageWidth  = wrapper->GetWidth();
	int imageHeight = wrapper->GetHeight();

	m_checkImage[level] = new GLubyte[imageWidth*imageHeight*4];

	int color;
	for (int i = 0; i < imageHeight; i++) {
		for (int j = 0; j < imageWidth; j++) {
			color = wrapper->GetValue(j,i);
			if(i*imageWidth*4 + j*4 +3 < imageWidth*imageHeight*4){
				m_checkImage[level][i*imageWidth*4 + j*4 +0] = (GLubyte)  GET_R(color);
				m_checkImage[level][i*imageWidth*4 + j*4 +1] = (GLubyte)  GET_G(color);
				m_checkImage[level][i*imageWidth*4 + j*4 +2] = (GLubyte)  GET_B(color);
				m_checkImage[level][i*imageWidth*4 + j*4 +3] = (GLubyte) 255;
			}
			else
				assert (0);
	  }
	}

	//Scale the image
    
    m_sWidth = nearestPower( imageWidth );
    m_sHeight = nearestPower( imageHeight );

    //scale texture image to 2^m by 2^n if necessary 
    if ( m_sWidth == imageWidth && m_sHeight == imageHeight ) {
         m_sImage[level] = (GLubyte *) m_checkImage[level];
    } else {
         m_sImage[level] = (GLubyte *)malloc( m_sHeight*m_sWidth*4*sizeof( GLubyte ) );
         gluScaleImage( GL_RGBA, imageWidth, imageHeight, 
                        GL_UNSIGNED_BYTE, m_checkImage[level],
                        m_sWidth, m_sHeight, GL_UNSIGNED_BYTE, m_sImage[level] );
		 delete m_checkImage[level];
    }
	
	// Define texture
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	if (!level) {
		// only generate for regular textures or for first level of mipmap
		glGenTextures(1, &m_texture);
	}

	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, m_sWidth, 
						m_sHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
						m_sImage[level]);
	//delete m_checkImage;
}


void MyTextureManager::setupTextureParams(MyMaterialManager& materialManager){
	m_materialManager = materialManager;
}

void MyTextureManager::set(){
	if (m_enabled){
		if (m_showTexture){
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//GL_DECAL);
			glBindTexture(GL_TEXTURE_2D, m_texture);
					
			GLuint sWrapMode = m_materialManager.m_sRepeat? GL_REPEAT :GL_CLAMP;
			GLuint tWrapMode = m_materialManager.m_tRepeat? GL_REPEAT :GL_CLAMP;

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrapMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrapMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_mipmapMode ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);

			
			if (m_materialManager.m_sAuto){
				glEnable(GL_TEXTURE_GEN_S);
				glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, m_materialManager.m_sType);
				GLfloat coord[] = {	m_materialManager.m_sCoord1, 
									m_materialManager.m_sCoord2, 
									m_materialManager.m_sCoord3, 
									m_materialManager.m_sCoord4};
				if (m_materialManager.m_sType == GL_EYE_LINEAR)
					glTexGenfv(GL_S, GL_EYE_PLANE, coord);
				else
					glTexGenfv(GL_S, GL_OBJECT_PLANE, coord);
			}
			else{
				glDisable(GL_TEXTURE_GEN_S);
			}

			if (m_materialManager.m_tAuto){
				glEnable(GL_TEXTURE_GEN_T);
				glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, m_materialManager.m_tType);
				GLfloat coord[] = {	m_materialManager.m_tCoord1, 
									m_materialManager.m_tCoord2, 
									m_materialManager.m_tCoord3, 
									m_materialManager.m_tCoord4};
				if (m_materialManager.m_sType == GL_EYE_LINEAR)
					glTexGenfv(GL_T, GL_EYE_PLANE, coord);
				else
					glTexGenfv(GL_T, GL_OBJECT_PLANE, coord);
			}
			else{
				glDisable(GL_TEXTURE_GEN_T);
			}

			

		  // glEnable(GL_AUTO_NORMAL);

		}
		else{
			glDisable(GL_TEXTURE_2D);
		}
	}
}


void MyTextureManager::enable(bool enable){
	m_enabled = enable;
}