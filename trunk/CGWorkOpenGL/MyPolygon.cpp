#include "MyPolygon.h"
#include "MyVertex.h"
#include "MyPostEffect.h"
#include "globals.h"
#include <list>
#include <new>

MyPolygon::MyPolygon(int nVertices, int norm_x, int norm_y, int norm_z)
	:	normal(norm_x, norm_y, norm_z)
{
	m_showTexture = false;
	m_texture = 0;
	m_vertices = new MyVertex[nVertices];
	if (NULL == m_vertices)
		throw std::bad_alloc("Cannot allocate vertices array");

	nextVertex = 0;

	normalInitialized = (normal) ? true : false;

	pfx_PerFace = pfx_PerVertex = false;

	c_x = c_y = c_z = 0;
}

MyPolygon::~MyPolygon(void)
{
	delete [] m_vertices;
}

void MyPolygon::setTexture(GLuint texture){
	m_texture = texture;
	m_showTexture = true;
}

#include <assert.h>
void MyPolygon::Draw(void)
{
	if (m_showTexture){
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glBindTexture(GL_TEXTURE_2D,m_texture);
	}
	else{
		glDisable(GL_TEXTURE_2D);
	}

	glBegin(GL_POLYGON);
	
	for (int i=0; i < nextVertex; i++)
	{
		if (torchEnabled)
		{
			// find the distance of the point from mouse cursor and set the color accordingly
			double	dx = m_vertices[i].x - cursor_x,
					dy = m_vertices[i].y - cursor_y,
					dz = m_vertices[i].z - cursor_z,
					d = sqrt(dx*dx + dy*dy + dz*dz),
					shade = 1 - (d/torch_range);

			if (shade < 0.1)//was 0.035
				shade = 0.1;	// maintain /some/ ambient light...

			glColor3d(shade, shade, shade);
		}

		//Draw texture		
		if (m_showTexture){
			//if (nextVertex !=4)
			//	assert(0);
			if (i==0)
				glTexCoord2f(0.0, 0.0);
			else if (i==1)
				glTexCoord2f(1.0, 0.0);
			else if (i==2)
				glTexCoord2f(1.0, 1.0);
			else if (i==3)
				glTexCoord2f(0.0, 1.0);
		}
		
		//Draw normal
		GLfloat norm[3]; 
		
		norm[0] = m_vertices[i].normal.m_x;
		norm[1] = m_vertices[i].normal.m_y;
		norm[2] = m_vertices[i].normal.m_z;

		if (norm[0]==0 &&norm[1]==0 && norm[2]==0){
			assert(0);
		}
		glNormal3fv(norm);

		//Draw vertex
		glVertex3d(m_vertices[i].x, m_vertices[i].y, m_vertices[i].z);
	}

	glEnd();

	//glFlush();
   glDisable(GL_TEXTURE_2D);

}

void MyPolygon::AddVertex(MyVertex& v)
{
	m_vertices[nextVertex++] = v;

	// update bounding-box
	bbox.update(v.x, v.y, v.z);

	// update center-point
	c_x = ((nextVertex-1)*c_x + v.x) / nextVertex;
	c_y = ((nextVertex-1)*c_y + v.y) / nextVertex;
	c_z = ((nextVertex-1)*c_z + v.z) / nextVertex;

	if (!normalInitialized && nextVertex == 3)
	{
		// we take the normal as the normalized cross-product of the first two edges, as soon
		// as we have a polygon with at least two edges.
		// for polygons with more than three, we do the same and hope that the entire polygon resides in
		// a single plane (otherwise a global normal for the face is undefined anyway)

		MyVector edge_a = MyVector(	m_vertices[0].x, m_vertices[0].y, m_vertices[0].z,
									m_vertices[1].x, m_vertices[1].y, m_vertices[1].z	);
		MyVector edge_b = MyVector(	m_vertices[1].x, m_vertices[1].y, m_vertices[1].z,
									m_vertices[2].x, m_vertices[2].y, m_vertices[2].z	);
		normal = edge_a.cross( edge_b );
		normal /= normal.Size();	// normalize to unit vector
	}
}


void MyPolygon::DrawNormals(bool faceNormal, bool vertexNormals, double size)
{
	double norm_size = size;

	if (!size)
	{
		double self_size = min( bbox.xSize(), bbox.ySize() );
		self_size = min( self_size, bbox.zSize() );

		norm_size = self_size / 10;	// we draw normals 1/10 the size of the face
	}

	// first draw the face normal, if available and requested
	if (this->normal && faceNormal)
	{
		MyVector n = normal * norm_size;

		glBegin(GL_LINES);
			glVertex3d(c_x, c_y, c_z);
			glVertex3d(c_x + n.m_x, c_y + n.m_y, c_z + n.m_z);
		glEnd();
	}

	// draw vertex normals, if requesteds
	if (vertexNormals)
	{
		MyVertex *v;

		for (int i = 0; i < nextVertex; i++)
		{
			v = &m_vertices[i];
			MyVector n = v->normal * norm_size;

			glBegin(GL_LINES);
				glVertex3d(v->x, v->y, v->z);
				glVertex3d(v->x + n.m_x, v->y + n.m_y, v->z + n.m_z);
			glEnd();
		}
	}
}

void MyPolygon::PushPostEffect(MyPostEffect* fx, long flags)
{
	pfx_PerFace = flags & PFX_FACES;
	pfx_PerVertex = flags & PFX_VERTICES;

	MyGlDrawable::PushPostEffect(fx);
}
