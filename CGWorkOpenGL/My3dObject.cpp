#include "My3dObject.h"
#include "MyTesselationManager.h"
#include <new>
#include <cstring>
#include <string>


My3dObject::My3dObject(string name, int nPolygons)
	: m_name(name)
{
	m_tesselator = NULL;
	nextPoly = 0;
	arrSize = nPolygons;

	// indicate all normals-display lists uninitialized
	for (int i = 0; i < 4; i++)
		m_NormalsDisplayList[i] = -1;

	m_polygons = new MyPolygon*[nPolygons];
	if (NULL == m_polygons)
		throw std::bad_alloc("Cannot allocate polygons array");

	for (int i=0; i<3; i++)
		m_color[i] = 1.0;	// default color is white

	m_alpha = 1.0;	// opaque by default
}

My3dObject::~My3dObject(void)
{
	for (int i = 0; i < 4; i++)
		if (m_NormalsDisplayList[i] > 0) glDeleteLists(m_NormalsDisplayList[i], 1);

	for (nextPoly--; nextPoly >= 0; nextPoly--)
		delete m_polygons[nextPoly];
	delete [] m_polygons;
}

void My3dObject::Draw(void)
{
	m_textureManager.set();

	glColor4d(m_color[0], m_color[1], m_color[2], m_alpha);

	for (int i=0; i<nextPoly; i++)
	{
		if (m_tesselator == NULL)
			m_polygons[i]->Draw();
		else
			m_polygons[i]->drawTesselated(m_tesselator);
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

void My3dObject::DrawNormals(bool faceNormals, bool vertexNormals, double normSize)
{
	double self_size = min( bbox.xSize(), bbox.ySize() );
	self_size = min( self_size, bbox.zSize() );

	if (normSize <= 0)
		normSize = self_size / 10;	// we draw normals 1/10 the size of the model by default

	for (int i = 0; i < nextPoly; i++)
	{
		// for each polygon
		m_polygons[i]->DrawNormals(faceNormals, vertexNormals, normSize);
	}
}

int My3dObject::GetNormalsDisplayList(bool faceNormals, bool vertexNormals, double normSize, bool recompile)
{
	int i = ((faceNormals ? 1 : 0) << 1) | (vertexNormals ? 1 : 0);

	if (m_NormalsDisplayList[i] < 0 || recompile)
	{
		// if we're recompiling where a list already exists, reuse the old index:
		m_NormalsDisplayList[i] = (m_NormalsDisplayList[i] >= 0) ? m_NormalsDisplayList[i] : glGenLists(1);
		glNewList(m_NormalsDisplayList[i], GL_COMPILE);
			this->DrawNormals(faceNormals, vertexNormals, normSize);
		glEndList();
	}

	return m_NormalsDisplayList[i];
}

void My3dObject::addPTexture(const char *str, bool fullPath){
	m_textureManager.addPTexture(str, fullPath, true);
}

void My3dObject::enableTexture(bool enable){
	m_textureManager.enable( enable );
}

void My3dObject::setTesselator(GLUtesselator* tesselator){
	m_tesselator = tesselator;
}

