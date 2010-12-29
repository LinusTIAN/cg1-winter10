#include "MyTesselationManager.h"
#include "globals.h"

MyTesselationManager::MyTesselationManager(void)
{
	m_tobj = NULL;
}

MyTesselationManager::~MyTesselationManager(void)
{
}

void CALLBACK myDrawVertex3dv(GLdouble *vec)
{
	glVertex3dv(vec);
}


void CALLBACK beginCallback(GLenum which)
{
	glBegin(which);
}

void CALLBACK endCallback(void)
{
	glEnd();
}

void CALLBACK errorCallback(GLenum errorCode)
{
   const GLubyte *estring;
   estring = gluErrorString(errorCode);
   fprintf (stderr, "Tessellation Error: %s\n", estring);
   exit (0);
}
void CALLBACK combineCallback(GLdouble coords[3], 
                     GLdouble *vertex_data[4],
                     GLfloat weight[4], GLdouble **dataOut )
{
   GLdouble *vertex;
   int i;

   vertex = (GLdouble *) malloc(6 * sizeof(GLdouble));
   vertex[0] = coords[0];
   vertex[1] = coords[1];
   vertex[2] = coords[2];
   for (i = 3; i < 7; i++)
      vertex[i] = weight[0] * vertex_data[0][i] 
                  + weight[1] * vertex_data[1][i]
                  + weight[2] * vertex_data[2][i] 
                  + weight[3] * vertex_data[3][i];
   *dataOut = vertex;
}

void* MyTesselationManager::setTesselation(bool isTess){

	if (m_tobj != NULL)
		gluDeleteTess((GLUtesselator*)m_tobj);

	if (isTess){
		m_tobj = gluNewTess();
		gluTessCallback((GLUtesselator*)m_tobj, GLU_TESS_VERTEX, (void (__stdcall *) (void)) &myDrawVertex3dv);
		gluTessCallback((GLUtesselator*)m_tobj, GLU_TESS_BEGIN, (void (__stdcall *) (void)) &beginCallback);
		gluTessCallback((GLUtesselator*)m_tobj, GLU_TESS_END, (void (__stdcall *) (void)) &endCallback);
		gluTessCallback((GLUtesselator*)m_tobj, GLU_TESS_ERROR, (void (__stdcall *) (void)) &errorCallback);   
		gluTessCallback((GLUtesselator*)m_tobj, GLU_TESS_COMBINE, (void (__stdcall *) (void)) & combineCallback);
	}
	else{
		m_tobj = NULL;
	}
	return m_tobj;
 /*
   	GLdouble v1[6] = {1.0, 0.0, 0.0,1,1,1};
	GLdouble v2[6] = {1.0, 1.0, 0.0,1,1,1};
	GLdouble v3[6] = {0.0, 1.0, 0.0,1,1,1};
	GLdouble v4[6] = {0.0, 0.0, 0.0,1,1,1};

	
	glColor3d( 1.0,  1.0,  1.0);

   gluTessBeginPolygon(tobj, NULL);
      gluTessBeginContour(tobj);			
			gluTessVertex(tobj, v1, v1);
			gluTessVertex(tobj, v2, v2);
			gluTessVertex(tobj, v3, v3);
			gluTessVertex(tobj, v4, v4);


      gluTessEndContour(tobj);
   gluTessEndPolygon(tobj);*/
}