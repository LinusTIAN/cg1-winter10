#include "MyFogPrameters.h"

#include "globals.h"

MyFogPrameters::MyFogPrameters(void)
{
	m_r = m_g = m_b = 0;
	m_density = 0.15;
	m_type = FOG_GL_EXP;

	enabled = false;
}

MyFogPrameters::~MyFogPrameters(void)
{
}


void MyFogPrameters::setupFog(){
	if (enabled)
   {
		glEnable(GL_FOG);
		GLfloat fogColor[4] = {	m_r / 255.0, 
								m_g / 255.0, 
								m_b / 255.0, 
								1.0};

		GLint fogMode = GL_EXP;
		
		switch (m_type){
			case FOG_GL_EXP:
				fogMode = GL_EXP;
				break;
			case FOG_GL_EXP2:
				fogMode = GL_EXP2;
				break;
			case FOG_GL_LINEAR:
				fogMode = GL_LINEAR;
				break;
		}
		glFogi (GL_FOG_MODE, fogMode);
		glFogfv (GL_FOG_COLOR, fogColor);
		glFogf (GL_FOG_DENSITY, m_density);
		glHint (GL_FOG_HINT, GL_DONT_CARE);
		glFogf (GL_FOG_START, 1.0);
		glFogf (GL_FOG_END, 5.0);
   }
	else{
		glDisable(GL_FOG);
	}
}
