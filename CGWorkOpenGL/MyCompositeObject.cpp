#include "MyCompositeObject.h"

MyCompositeObject::MyCompositeObject(void)
{
	m_arrSize = 20;
	m_objects = new My3dObject*[m_arrSize];
	m_nextObj = 0;

	// signal all display lists uninitialized
	for (int i = 0; i < 4; i++)
		m_NormalsDisplayList[i] = -1;
	for (int i = 0; i < 3; i++)
		m_compDisplayLists[i] = -1;
}

MyCompositeObject::~MyCompositeObject(void)
{
	for (int i = 0; i < 4; i++)
		if (m_NormalsDisplayList[i] > 0) glDeleteLists(m_NormalsDisplayList[i], 1);
	for (int i = 0; i < 3; i++)
		if (m_compDisplayLists[i] > 0) glDeleteLists(m_compDisplayLists[i], 1);

	for (m_nextObj--; m_nextObj >= 0; m_nextObj--)
		delete m_objects[m_nextObj];
	delete [] m_objects;
}


void MyCompositeObject::addObjectRef(My3dObject* obj)
{
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

void MyCompositeObject::Draw(OBJECT_SELECTOR_T to_draw)
{
	for (int i = 0; i < m_nextObj; i++) {
		if (	(to_draw&SELECT_OPAQUE && m_objects[i]->m_alpha == 1.0) ||
				(to_draw&SELECT_TRANSPARENT && m_objects[i]->m_alpha != 1.0) ) {
			m_objects[i]->Draw();
		}
	}
}

int MyCompositeObject::GetDisplayList(OBJECT_SELECTOR_T to_draw, bool recompile)
{
	int i = to_draw - 1;	// make so first value is 0 and not 1, to use as index into array

	if (m_compDisplayLists[i] <= 0 || recompile)
	{
		// if we're recompiling where a list already exists, reuse the old index:
		m_compDisplayLists[i] = (m_compDisplayLists[i] > 0) ? m_compDisplayLists[i] : glGenLists(1);
		glNewList(m_compDisplayLists[i], GL_COMPILE);
			this->Draw(to_draw);
		glEndList();
	}

	return m_compDisplayLists[i];
}

void MyCompositeObject::changeColor(double r, double g, double b)
{
	for (int i=0; i < m_nextObj; i++){
		m_objects[i]->m_color[0] = r;
		m_objects[i]->m_color[1] = g;
		m_objects[i]->m_color[2] = b;
	}
}

void MyCompositeObject::DrawNormals(bool faceNormals, bool vertexNormals)
{
	if (!faceNormals && !vertexNormals)
		return;

	double self_size = min( bbox.xSize(), bbox.ySize() );
	self_size = min( self_size, bbox.zSize() );

	double norm_size = self_size / 10;	// we draw normals 1/10 the size of the model

	for (int i = 0; i < m_nextObj; i++)
	{
		// for each sub-object
		m_objects[i]->DrawNormals(faceNormals, vertexNormals, norm_size);
	}
}

int MyCompositeObject::GetNormalsDisplayList(bool faceNormals, bool vertexNormals, bool recompile)
{
	int i = ((faceNormals ? 1 : 0) << 1) | (vertexNormals ? 1 : 0);

	if (m_NormalsDisplayList[i] <= 0 || recompile)
	{
		// if we're recompiling where a list already exists, reuse the old index:
		m_NormalsDisplayList[i] = (m_NormalsDisplayList[i] > 0) ? m_NormalsDisplayList[i] : glGenLists(1);
		if (m_NormalsDisplayList[i] <= 0)
			::MessageBox(NULL, "Invalid display list index", NULL, MB_OK);
		glNewList(m_NormalsDisplayList[i], GL_COMPILE);
			this->DrawNormals(faceNormals, vertexNormals);
		glEndList();
	}

	return m_NormalsDisplayList[i];
}

