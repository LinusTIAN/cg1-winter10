#include "MyGlDrawable.h"
#include "MyPostEffect.h"
#include <windows.h>
#include "gl\gl.h"    // Include the standard OpenGL  headers
#include "gl\glu.h"   // Add the utility library

MyGlDrawable::MyGlDrawable(void)
{
	m_displayList = -1;
}

MyGlDrawable::~MyGlDrawable(void)
{
	if (m_displayList >= 0)
		glDeleteLists(m_displayList, 1);
}

int MyGlDrawable::GetDisplayList(bool recompile)
{
	//recompile = true;
	if (m_displayList < 0 || recompile)
	{
		// if we're recompiling where a list already exists, reuse the old index:
		m_displayList = (m_displayList >= 0) ? m_displayList : glGenLists(1);
		glNewList(m_displayList, GL_COMPILE);
			this->Draw();
		glEndList();
	}

	return m_displayList;
}

void MyGlDrawable::DrawBoundingBox(void)
{
	glBegin(GL_LINE_LOOP);
		glVertex3d(bbox.x_min, bbox.y_min, bbox.z_min);
		glVertex3d(bbox.x_max, bbox.y_min, bbox.z_min);
		glVertex3d(bbox.x_max, bbox.y_max, bbox.z_min);
		glVertex3d(bbox.x_min, bbox.y_max, bbox.z_min);
	glEnd();

	glBegin(GL_LINE_LOOP);
		glVertex3d(bbox.x_min, bbox.y_min, bbox.z_max);
		glVertex3d(bbox.x_max, bbox.y_min, bbox.z_max);
		glVertex3d(bbox.x_max, bbox.y_max, bbox.z_max);
		glVertex3d(bbox.x_min, bbox.y_max, bbox.z_max);
	glEnd();

	glBegin(GL_LINES);
		glVertex3d(bbox.x_min, bbox.y_min, bbox.z_min);
		glVertex3d(bbox.x_min, bbox.y_min, bbox.z_max);
		glVertex3d(bbox.x_max, bbox.y_min, bbox.z_min);
		glVertex3d(bbox.x_max, bbox.y_min, bbox.z_max);
		glVertex3d(bbox.x_min, bbox.y_max, bbox.z_min);
		glVertex3d(bbox.x_min, bbox.y_max, bbox.z_max);
		glVertex3d(bbox.x_max, bbox.y_max, bbox.z_min);
		glVertex3d(bbox.x_max, bbox.y_max, bbox.z_max);
	glEnd();
}
