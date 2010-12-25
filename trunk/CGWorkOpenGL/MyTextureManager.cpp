#include "MyTextureManager.h"

#include "globals.h"
#include <new>
#include <cstring>
#include <string>
#include <assert.h>

using namespace std;


MyTextureManager::MyTextureManager(void)
{
	m_enabled = true;
	m_showTexture = false;
}

MyTextureManager::~MyTextureManager(void)
{
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


void MyTextureManager::addPTexture(const char *str, bool fullPath){
	
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
		fileName ="pics\\"+fileName+ "png";
	}

	PngWrapper wrapper;
	wrapper.SetFileName(fileName.c_str());
	if (!wrapper.ReadPng())
		return ;

	m_showTexture = true;
	bindTexture(&wrapper);
}


void MyTextureManager::bindTexture(PngWrapper* wrapper){
	
	// Read the texture image
	int imageWidth  = wrapper->GetWidth();
	int imageHeight = wrapper->GetHeight();

	GLubyte* checkImage = new GLubyte[imageWidth*imageHeight*4*sizeof(GLubyte)];

	int color;
	for (int i = 0; i < imageHeight; i++) {
		for (int j = 0; j < imageWidth; j++) {
			color = wrapper->GetValue(j,i);
			if(i*imageWidth*4 + j*4 +3 < imageWidth*imageHeight*4){
				checkImage[i*imageWidth*4 + j*4 +0] = (GLubyte)  GET_R(color);
				checkImage[i*imageWidth*4 + j*4 +1] = (GLubyte)  GET_G(color);
				checkImage[i*imageWidth*4 + j*4 +2] = (GLubyte)  GET_B(color);
				checkImage[i*imageWidth*4 + j*4 +3] = (GLubyte) 255;
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
         m_sImage = (GLubyte *) checkImage;
    } else {
         m_sImage = (GLubyte *)malloc( m_sHeight*m_sWidth*4*sizeof( GLubyte ) );
         gluScaleImage( GL_RGBA, imageWidth, imageHeight, 
                        GL_UNSIGNED_BYTE, checkImage,
                        m_sWidth, m_sHeight, GL_UNSIGNED_BYTE, m_sImage );
		 delete checkImage;
    }
	
	// Define texture
	m_texture = 0;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1,  &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_sWidth, 
						m_sHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
						m_sImage);

	
}


void MyTextureManager::setupTextureParams(MyMaterialManager& materialManager){
	m_materialManager = materialManager;
}

void MyTextureManager::set(){
	if (m_enabled){
		if (m_showTexture){
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//GL_DECAL);
			glBindTexture(GL_TEXTURE_2D,m_texture);
					
			GLuint sWrapMode = m_materialManager.m_sRepeat? GL_REPEAT :GL_CLAMP;
			GLuint tWrapMode = m_materialManager.m_tRepeat? GL_REPEAT :GL_CLAMP;

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrapMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrapMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,   GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,   GL_NEAREST);
		}
		else{
			glDisable(GL_TEXTURE_2D);
		}
	}
}


void MyTextureManager::enable(bool enable){
	m_enabled = enable;
}