#include "MyTesselationManager.h"
#include "globals.h"

MyTesselationManager::MyTesselationManager(void)
{
}

MyTesselationManager::~MyTesselationManager(void)
{
}



void beginCallback(GLenum which)
{
	glBegin(which);
}

void endCallback(void)
{
	glEnd();
}

void errorCallback(GLenum errorCode)
{
   const GLubyte *estring;
   estring = gluErrorString(errorCode);
   fprintf (stderr, "Tessellation Error: %s\n", estring);
   exit (0);
}
void combineCallback(GLdouble coords[3], 
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

void MyTesselationManager::Init(){
	GLUtesselator* tobj = gluNewTess();
	gluTessCallback(tobj, GLU_TESS_VERTEX, (void (__stdcall *) (void)) &glVertex3dv);
	gluTessCallback(tobj, GLU_TESS_BEGIN, (void (__stdcall *) (void)) &beginCallback);
	gluTessCallback(tobj, GLU_TESS_END, (void (__stdcall *) (void)) &endCallback);
	gluTessCallback(tobj, GLU_TESS_ERROR, (void (__stdcall *) (void)) &errorCallback);   
	gluTessCallback(tobj, GLU_TESS_COMBINE, (void (__stdcall *) (void)) & combineCallback);
 
   	GLdouble v1[3] = {252.0, 153.0, 0.0};
	GLdouble v2[3] = {252.0, 47.0, 0.0};
	GLdouble v3[3] = {393.0, 47.0, 0.0};
	GLdouble v4[3] = {393.0, 153.0, 0.0};


   gluTessBeginPolygon(tobj, NULL);
      gluTessBeginContour(tobj);			
			gluTessVertex(tobj, v1, v1);
			gluTessVertex(tobj, v2, v2);
			gluTessVertex(tobj, v3, v3);
			gluTessVertex(tobj, v4, v4);


      gluTessEndContour(tobj);
   gluTessEndPolygon(tobj);


}