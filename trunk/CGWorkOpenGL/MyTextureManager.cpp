#include "MyTextureManager.h"

#include "globals.h"
#include <new>
#include <cstring>
#include <string>

using namespace std;


MyTextureManager::MyTextureManager(void)
{
}

MyTextureManager::~MyTextureManager(void)
{
}



int MyTextureManager::addPTexture(const char *str, bool fullPath){
	
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
		return 0;

	return setUpTexture(&wrapper);
}


int MyTextureManager::setUpTexture(PngWrapper* wrapper){

	GLuint texture = 0;
/*
	GLubyte*** checkImage = new GLubyte**[wrapper->GetHeight()];//[wrapper->GetWidth()][4];
	for(int i=0; i<wrapper->GetHeight(); i++){
		checkImage[i] = new GLubyte*[wrapper->GetWidth()];
		for(int j=0; j<wrapper->GetWidth(); j++){
			checkImage[i][j] = new GLubyte[4];
		}
	}*/
	//TODO!!! arr size!!!

	GLubyte checkImage[80][65][4];
	int imageWidth = 64;
	int imageHeight = 64;

	/*int i, j, c,color;
	for (i = 0; i < imageHeight; i++) {
		for (j = 0; j < imageWidth; j++) {
			color = wrapper->GetValue(j,i);
			checkImage[i][j][0] = (GLubyte)  GET_R(color);
			checkImage[i][j][1] = (GLubyte)  GET_G(color);
			checkImage[i][j][2] = (GLubyte)  GET_B(color);
			checkImage[i][j][3] = (GLubyte) 255;
	  }
	}*/

	/*int i, j, c,color;
	for (i = 0; i < imageHeight; i++) {
		for (j = 0; j < imageWidth; j++) {
			checkImage[i][j][0] = (GLubyte)  0;
			checkImage[i][j][1] = (GLubyte)  0;
			checkImage[i][j][2] = (GLubyte)  255;
			checkImage[i][j][3] = (GLubyte) 255;
			if (i%2==0  ){
				checkImage[i][j][0] = (GLubyte)  255;
				checkImage[i][j][2] = (GLubyte)  0;
			}

			if (j%8==0 ){
				checkImage[i][j][0] = (GLubyte)  0;
				checkImage[i][j][1] = (GLubyte)  255;
				checkImage[i][j][2] = (GLubyte)  0;
			}
	  }
	}*/

	int i, j, c;
    
   for (i = 0; i < imageHeight; i++) {
      for (j = 0; j < imageWidth; j++) {
         c = ((((i&0x8)==0)^((j&0x8))==0))*255;
         checkImage[i][j][0] = (GLubyte) c;
         checkImage[i][j][1] = (GLubyte) c;
         checkImage[i][j][2] = (GLubyte) c;
         checkImage[i][j][3] = (GLubyte) 255;
      }
   }


	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,   GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,   GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, 
						imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
						checkImage);

	return texture;
}