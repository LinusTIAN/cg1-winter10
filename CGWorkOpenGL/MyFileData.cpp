#include "MyFileData.h"

MyFileData::MyFileData(void)
{
	m_arrSize = 20;
	m_objects = new My3dObject*[m_arrSize];
	m_nextObj = 0;
}

MyFileData::~MyFileData(void)
{
	for (m_nextObj--; m_nextObj >= 0; m_nextObj--)
		delete m_objects[m_nextObj];
	delete [] m_objects;
}


void MyFileData::addObjectRef(My3dObject* obj){
	
	if (m_arrSize <= m_nextObj )
	{
		// reallocate with more memory
		My3dObject **new_mem = new My3dObject*[m_arrSize*2];
		if (NULL == new_mem){
			throw std::bad_alloc("Cannot allocate objects array");
		}
		std::memcpy(new_mem, m_objects, m_nextObj*sizeof(My3dObject*));
		delete [] m_objects;
		m_objects = new_mem;

		m_arrSize *= 2;
	}

	m_objects[m_nextObj++] = obj;
	
	bbox.update(obj->bbox);
}


void MyFileData::draw(bool torchEnabled, bool showFaceNormals, bool showVertexNormals, bool recompile){
	for (int i=0; i < m_nextObj; i++){
		if (!torchEnabled){
			// can use the compiled display list
			glCallList( m_objects[i]->GetDisplayList(recompile) );
		}
		else
		{
			// torch requires we redraw from scratch each time!
			m_objects[i]->Draw();
		}
		if (showVertexNormals || showFaceNormals)
			glCallList( m_objects[i]->GetNormalsDisplayList(showFaceNormals, showVertexNormals) );
	}

}
void MyFileData::drawBoundingBox(){
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

void MyFileData::init(bool showFaceNormals, bool showVertexNormals){
	// make it generate the display lists in advance
	for (int i=0; i < m_nextObj; i++){
		m_objects[i]->GetDisplayList(true);
		m_objects[i]->GetNormalsDisplayList(showFaceNormals, showVertexNormals, true);
	}
}

void MyFileData::changeColor(int r,int g,int b){
	for (int i=0; i < m_nextObj; i++){
		m_objects[i]->m_color[0] = r;
		m_objects[i]->m_color[1] = g;
		m_objects[i]->m_color[2] = b;
	}
}

