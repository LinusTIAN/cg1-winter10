#include <assert.h>
#include "MyVertex.h"

MyVertex::MyVertex(void)
	:	x(0), y(0), z(0),
		normal(0, 0, 0)
{
	m_hasUV = false;
}

MyVertex::MyVertex(double x, double y, double z)
	:	x(x), y(y), z(z),
		normal(0, 0, 0)
{
	m_hasUV = false;
}

MyVertex::~MyVertex(void)
{
}

void MyVertex::setNormal(double norm_x, double norm_y, double norm_z){
	normal.m_x = norm_x;
	normal.m_y = norm_y;
	normal.m_z = norm_z;
	normal /= normal.Size();	// normalize to unit vector
}

void MyVertex::setUV(double u, double v){
	m_u = u;
	m_v = v;
	m_hasUV = true;
}

void MyVertex::Draw() {
	// draw texture
	if (m_hasUV){
		glTexCoord2f(m_u, m_v);
	}
	else{
		int y;
		y++;

	}
	/*else{
		if (iterationNum==0)
			glTexCoord2f(0.0, 0.0);
		else if (iterationNum==1)
			glTexCoord2f(1.0, 0.0);
		else if (iterationNum==2)
			glTexCoord2f(1.0, 1.0);
		else if (iterationNum==3)
			glTexCoord2f(0.0, 1.0);
	}*/

	//draw normal
	GLfloat norm[3] = {normal.m_x, normal.m_y, normal.m_z}; 
	assert(! (norm[0]==0 && norm[1]==0 && norm[2]==0)); //TODO check which model hasn't any normals
	glNormal3fv(norm);

	//draw vertex
	glVertex3d(x, y, z);
}
