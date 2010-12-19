#include "MyMaterialManager.h"
#include "globals.h"


MyMaterialManager::MyMaterialManager(void)
{
	m_ambient = 0.2;
    m_diffuse = 0.8;
    m_specular = 1.0;
	m_shininess = 32;
}

MyMaterialManager::~MyMaterialManager(void)
{
}

void MyMaterialManager::setupMaterialInScene(){
	GLfloat mat_shininess[] = { m_shininess };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
	
	GLfloat mat_specular[] = { m_specular, m_specular, m_specular, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	
	GLfloat mat_diffuse[] = { m_diffuse, m_diffuse, m_diffuse, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	
	GLfloat mat_ambient[] = { m_ambient, m_ambient, m_ambient, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
}
