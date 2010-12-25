#include "MyMaterialManager.h"
#include "globals.h"


MyMaterialManager::MyMaterialManager(void)
{
	reset();
}

MyMaterialManager::~MyMaterialManager(void)
{
}

void MyMaterialManager::setupMaterialInScene(){
	GLfloat mat_shininess[] = { (GLfloat) m_shininess };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
	
	GLfloat mat_specular[] = { m_specular, m_specular, m_specular, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	
	GLfloat mat_diffuse[] = { m_diffuse, m_diffuse, m_diffuse, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	
	GLfloat mat_ambient[] = { m_ambient, m_ambient, m_ambient, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
}

void MyMaterialManager::reset(){

	m_ambient = 0.2f;
    m_diffuse = 0.8f;
    m_specular = 1.0;
	m_shininess = 32;

	m_sRepeat = m_tRepeat = true;
	
	m_sAuto = m_tAuto = false;
	m_sType = m_tType = 1;
	m_sCoord1 = 0.0;
	m_sCoord2 = 1.0;
	m_sCoord3 = 1.0;
	m_sCoord4 = 0.0;

	m_tCoord1 = 0.0;
	m_tCoord2 = 1.0;
	m_tCoord3 = 1.0;
	m_tCoord4 = 0.0;
}
