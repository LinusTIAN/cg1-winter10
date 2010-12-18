#include "My3dObject.h"
#include <new>
#include <cstring>
#include <string>


My3dObject::My3dObject(int nPolygons)
{
	m_showTexture = false;
	nextPoly = 0;
	arrSize = nPolygons;

	// indicate all normals-display lists uninitialized
	for (int i = 0; i < 4; i++)
		m_NormalsDisplayList[i] = -1;

	m_polygons = new MyPolygon*[nPolygons];
	if (NULL == m_polygons)
		throw std::bad_alloc("Cannot allocate polygons array");

	
	for (int i=0; i<3; i++)
		m_color[i] = -1;	// color is uninitialized
}

My3dObject::~My3dObject(void)
{
	for (nextPoly--; nextPoly >= 0; nextPoly--)
		delete m_polygons[nextPoly];
	delete [] m_polygons;
}

void My3dObject::Draw(void)
{
	glColor3d(m_color[0], m_color[1], m_color[2]);

	for (int i=0; i<nextPoly; i++){
		if (m_showTexture){
			m_polygons[i]->setTexture(m_textureName);
		}
		m_polygons[i]->Draw();
	}
}

void My3dObject::AddPolyRef(MyPolygon* p)
{
	if (arrSize <= nextPoly )
	{
		// reallocate with more memory
		MyPolygon **new_mem = new MyPolygon*[arrSize*2];
		if (NULL == new_mem)
			throw std::bad_alloc("Cannot allocate polygons array");
		std::memcpy(new_mem, m_polygons, nextPoly*sizeof(MyPolygon*));
		delete [] m_polygons;
		m_polygons = new_mem;

		arrSize *= 2;
	}

	m_polygons[nextPoly++] = p;
	
	bbox.update(p->bbox);
}

void My3dObject::DrawNormals(bool faceNormals, bool vertexNormals)
{
	double self_size = min( bbox.xSize(), bbox.ySize() );
	self_size = min( self_size, bbox.zSize() );

	double norm_size = self_size / 30;	// we draw normals 1/10 the size of the model

	for (int i = 0; i < nextPoly; i++)
	{
		// for each polygon
		m_polygons[i]->DrawNormals(faceNormals, vertexNormals, norm_size);
	}
}

int My3dObject::GetNormalsDisplayList(bool faceNormals, bool vertexNormals, bool recompile)
{
	int i = ((faceNormals ? 1 : 0) << 1) | (vertexNormals ? 1 : 0);

	if (m_NormalsDisplayList[i] < 0 || recompile)
	{
		// if we're recompiling where a list already exists, reuse the old index:
		m_NormalsDisplayList[i] = (m_NormalsDisplayList[i] >= 0) ? m_NormalsDisplayList[i] : glGenLists(1);
		glNewList(m_NormalsDisplayList[i], GL_COMPILE);
			this->DrawNormals(faceNormals, vertexNormals);
		glEndList();
	}

	return m_NormalsDisplayList[i];
}

void My3dObject::PushPostEffect(MyPostEffect* fx, long flags)
{
	for (int i = 0; i < nextPoly; i++)
		m_polygons[i]->PushPostEffect(fx, flags);
}

void My3dObject::PopPostEffect()
{
	for (int i = 0; i < nextPoly; i++)
		m_polygons[i]->PopPostEffect();
}


void My3dObject::addPTexture(const char *str, bool fullPath){
	m_textureName = m_textureManager.addPTexture(str, fullPath);
	if (m_textureName >0)
		m_showTexture = true;
}
