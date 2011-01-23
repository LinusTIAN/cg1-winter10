#include "MyLight.h"
#include "globals.h"

// make sure the constants we need for specifying that specular highlights be applied
// AFTER texture mapping are available
#ifndef GL_LIGHT_MODEL_COLOR_CONTROL
	#define GL_LIGHT_MODEL_COLOR_CONTROL 0x81F8
#endif

#ifndef GL_SINGLE_COLOR
	#define GL_SINGLE_COLOR 0x81F9
#endif

#ifndef GL_SEPARATE_SPECULAR_COLOR
	#define GL_SEPARATE_SPECULAR_COLOR 0x81FA
#endif 


MyLight::MyLight(void)
{
}

MyLight::~MyLight(void)
{
}

void MyLight::setupGeneralLight(bool show, LightParams& params ){
	if (!show){
		glDisable(GL_LIGHTING);
		return;
	}

	m_params = params;


	glEnable(GL_LIGHTING); 
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_COLOR_MATERIAL);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	GLfloat lmodel_ambient[] = { m_params.colorR/255.0, m_params.colorG/255.0, m_params.colorB/255.0, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	// maintain specular highlights in texture mode
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);

	//glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT, GL_NICEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}


void MyLight::showLight(LightParams& light, int num){
		
	GLenum lightSource = GL_LIGHT0 + num;
	if ( ! light.enabled){
		glDisable(lightSource);
		return;
	}

	GLfloat light_position[]  = {light.posX, light.posY, light.posZ, 1.0 };
	GLfloat light_direction[] = {light.dirX, light.dirY, light.dirZ, 0.0 };

	switch (light.type){
		//Directional light
		case LIGHT_TYPE_DIRECTIONAL:{
				light_position[3] = 0.0;
				glLightfv(lightSource, GL_POSITION,		light_position);
				glLightf (lightSource, GL_SPOT_CUTOFF,	180.0);
			}
			break;
		//Positional light
		case LIGHT_TYPE_POINT:{
				light_position[3] = 1.0;
				glLightfv(lightSource, GL_POSITION,		light_position);
				glLightf (lightSource, GL_SPOT_CUTOFF,	180.0);
			 }
			break;
		//Spot light
		case LIGHT_TYPE_SPOT:{
				light_position[3] = 1.0;
				glLightfv(lightSource, GL_POSITION,		light_position);
				glLightfv(lightSource, GL_SPOT_DIRECTION, light_direction);

				glLightf (lightSource, GL_SPOT_CUTOFF,	45.0);
			 }
			break;
	}

	GLfloat mat_color[] = { light.colorR/255.0, light.colorG/255.0, light.colorB/255.0, 1.0 };
	GLfloat ambient_color[] = { 0, 0, 0, 1.0 };

	glLightfv(lightSource, GL_DIFFUSE,  mat_color);
	glLightfv(lightSource, GL_SPECULAR, mat_color);
	glLightfv(lightSource, GL_AMBIENT,  ambient_color);



	glEnable(lightSource);
}
