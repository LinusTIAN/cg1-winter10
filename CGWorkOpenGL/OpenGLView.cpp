// OpenGLView.cpp : implementation of the COpenGLView class
//
#include "stdafx.h"
#include "OpenGL.h"

#include "OpenGLDoc.h"
#include "OpenGLView.h"

#include <iostream>
using std::cout;
using std::endl;
#include <math.h>

#include "MaterialDlg.h"
#include "LightDialog.h"

#include "MouseSensitivityDialog.h"
#include "MaterialDlg.h"
#include "FogDialog.h"
#include "LoadTextureDlg.h"

#include "globals.h"

#include <climits>

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "PngWrapper.h"
#include "iritSkel.h"

#define _USE_MATH_DEFINES 
#include <cmath>

// For Status Bar access
#include "MainFrm.h"

// Use this macro to display text messages in the status bar.
#define STATUS_BAR_TEXT(str) (((CMainFrame*)GetParentFrame())->getStatusBar().SetWindowText(str))


/////////////////////////////////////////////////////////////////////////////
// COpenGLView

IMPLEMENT_DYNCREATE(COpenGLView, CView)

BEGIN_MESSAGE_MAP(COpenGLView, CView)
	//{{AFX_MSG_MAP(COpenGLView)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_LOAD, OnFileLoad)
	ON_COMMAND(ID_VIEW_ORTHOGRAPHIC, OnViewOrthographic)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ORTHOGRAPHIC, OnUpdateViewOrthographic)
	ON_COMMAND(ID_VIEW_PERSPECTIVE, OnViewPerspective)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PERSPECTIVE, OnUpdateViewPerspective)
	ON_COMMAND(ID_ACTION_ROTATE, OnActionRotate)
	ON_UPDATE_COMMAND_UI(ID_ACTION_ROTATE, OnUpdateActionRotate)
	ON_COMMAND(ID_ACTION_SCALE, OnActionScale)
	ON_UPDATE_COMMAND_UI(ID_ACTION_SCALE, OnUpdateActionScale)
	ON_COMMAND(ID_ACTION_TRANSLATE, OnActionTranslate)
	ON_UPDATE_COMMAND_UI(ID_ACTION_TRANSLATE, OnUpdateActionTranslate)
	ON_COMMAND(ID_AXIS_X, OnAxisX)
	ON_UPDATE_COMMAND_UI(ID_AXIS_X, OnUpdateAxisX)
	ON_COMMAND(ID_AXIS_Y, OnAxisY)
	ON_UPDATE_COMMAND_UI(ID_AXIS_Y, OnUpdateAxisY)
	ON_COMMAND(ID_AXIS_Z, OnAxisZ)
	ON_UPDATE_COMMAND_UI(ID_AXIS_Z, OnUpdateAxisZ)
	ON_COMMAND(ID_LIGHT_SHADING_FLAT, OnLightShadingFlat)
	ON_UPDATE_COMMAND_UI(ID_LIGHT_SHADING_FLAT, OnUpdateLightShadingFlat)
	ON_COMMAND(ID_LIGHT_SHADING_GOURAUD, OnLightShadingGouraud)
	ON_UPDATE_COMMAND_UI(ID_LIGHT_SHADING_GOURAUD, OnUpdateLightShadingGouraud)
	ON_COMMAND(ID_LIGHT_CONSTANTS, OnLightConstants)
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_ACTION_OBJECTSPACE, &COpenGLView::OnActionObjectspace)
	ON_UPDATE_COMMAND_UI(ID_ACTION_OBJECTSPACE, &COpenGLView::OnUpdateActionObjectspace)
	ON_COMMAND(ID_ACTION_VIEWSPACE, &COpenGLView::OnActionViewspace)
	ON_UPDATE_COMMAND_UI(ID_ACTION_VIEWSPACE, &COpenGLView::OnUpdateActionViewspace)
	ON_COMMAND(ID_OPTIONS_MOUSESENSITIVITY, &COpenGLView::OnOptionsMousesensitivity)
	ON_COMMAND(ID_OPTIONS_CHANGEWIRECOLOR, &COpenGLView::OnOptionsChangewirecolor)
	ON_COMMAND(ID_OPTIONS_CHANGEBACKGROUNDCOLOR, &COpenGLView::OnOptionsChangebackgroundcolor)
	ON_COMMAND(ID_OPTIONS_DRAWBOUNDINGBOX, &COpenGLView::OnOptionsDrawboundingbox)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_DRAWBOUNDINGBOX, &COpenGLView::OnUpdateOptionsDrawboundingbox)
	ON_COMMAND(ID_OPTIONS_SHOWVERTICESNORMALS, &COpenGLView::OnOptionsShowverticesnormals)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_SHOWVERTICESNORMALS, &COpenGLView::OnUpdateOptionsShowverticesnormals)
	ON_COMMAND(ID_OPTIONS_SHOWFACESNORMALS, &COpenGLView::OnOptionsShowfacesnormals)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_SHOWFACESNORMALS, &COpenGLView::OnUpdateOptionsShowfacesnormals)
	ON_COMMAND(ID_OPTIONS_PERSPECTIVECONTROL, &COpenGLView::OnOptionsPerspectivecontrol)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_OPTIONS_TORCH, &COpenGLView::OnOptionsTorch)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_TORCH, &COpenGLView::OnUpdateOptionsTorch)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_AXIS_XY, &COpenGLView::OnAxisXy)
	ON_UPDATE_COMMAND_UI(ID_AXIS_XY, &COpenGLView::OnUpdateAxisXy)
	ON_COMMAND(ID_FILE_RESET, &COpenGLView::OnFileReset)
	ON_COMMAND(ID_ACTION_UNIFORMSCALING, &COpenGLView::OnActionUniformscaling)
	ON_UPDATE_COMMAND_UI(ID_ACTION_UNIFORMSCALING, &COpenGLView::OnUpdateActionUniformscaling)
	ON_COMMAND(ID_SHADING_WIREFRAME, &COpenGLView::OnShadingWireframe)
	ON_UPDATE_COMMAND_UI(ID_SHADING_WIREFRAME, &COpenGLView::OnUpdateShadingWireframe)
	ON_COMMAND(ID_MATERIAL_LOADTEXTURE, &COpenGLView::OnMaterialLoadtexture)
	ON_COMMAND(ID_OPTIONS_BACKFACESCULLING, &COpenGLView::OnOptionsBackfacesculling)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_BACKFACESCULLING, &COpenGLView::OnUpdateOptionsBackfacesculling)
	ON_COMMAND(ID_LIGHT_FOG, &COpenGLView::OnLightFog)
	ON_COMMAND(ID_MATERIAL_PROPERTIES, &COpenGLView::OnMaterialProperties)
	ON_COMMAND(ID_ACTION_TEXTURETRANSFORMATIONS, &COpenGLView::OnActionTexturetransformations)
	ON_UPDATE_COMMAND_UI(ID_ACTION_TEXTURETRANSFORMATIONS, &COpenGLView::OnUpdateActionTexturetransformations)
	ON_COMMAND(ID_RESET_LIGHT, &COpenGLView::OnResetLight)
	ON_COMMAND(ID_RESET_VIEW, &COpenGLView::OnResetView)
	ON_COMMAND(ID_MATERIAL_TESSELATION, &COpenGLView::OnMaterialTesselation)
	ON_UPDATE_COMMAND_UI(ID_MATERIAL_TESSELATION, &COpenGLView::OnUpdateMaterialTesselation)
	ON_COMMAND(ID_MATERIAL_LOADMIPMAP, &COpenGLView::OnMaterialLoadmipmap)
END_MESSAGE_MAP()


// A patch to fix GLaux disappearance from VS2005 to VS2008
void auxSolidCone(GLdouble radius, GLdouble height) {
        GLUquadric *quad = gluNewQuadric();
        gluQuadricDrawStyle(quad, GLU_FILL);
        gluCylinder(quad, radius, 0.0, height, 20, 20);
        gluDeleteQuadric(quad);
}

/////////////////////////////////////////////////////////////////////////////
// COpenGLView construction/destruction

COpenGLView::COpenGLView()
: m_LastTransformPoint(0)
, m_lastCtrlPoint(0)
, m_mouseScreenZ(0)
{
	m_showTesselation = false;
	m_mouseSensitivity = 50;
	m_showBoundingBox = false; 
	m_showVertexNormals = false;
	m_showFaceNormals = false;
	m_recompile = false;
	m_showBackFaces = true;
	m_backgroundColor[0] = m_backgroundColor[1] = m_backgroundColor[2] = 0;

	// Set default values
	m_nAxis = ID_AXIS_X;
	m_nAction = ID_ACTION_ROTATE;
	m_nView = ID_VIEW_ORTHOGRAPHIC;	
	m_nSpace = ID_ACTION_VIEWSPACE;
	m_bIsPerspective = false;

	m_nLightShading = ID_LIGHT_SHADING_GOURAUD;


	//init the first light to be enabled
	m_lights[LIGHT_ID_1].enabled=true;

	lightReset();
}

COpenGLView::~COpenGLView()
{
}


/////////////////////////////////////////////////////////////////////////////
// COpenGLView diagnostics

#ifdef _DEBUG
void COpenGLView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLDoc* COpenGLView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLDoc)));
	return (COpenGLDoc*)m_pDocument;
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// COpenGLView Window Creation - Linkage of windows to OpenGL

BOOL COpenGLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	// An OpenGL window must be created with the following
	// flags and must NOT include CS_PARENTDC for the
	// class style.

	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}



int COpenGLView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	InitializeOpenGL();

	return 0;
}


// This method initialized the OpenGL system.
BOOL COpenGLView::InitializeOpenGL()
{
	m_pDC = new CClientDC(this);

	if ( NULL == m_pDC ) { // failure to get DC
		::AfxMessageBox("Couldn't get a valid DC.");
		return FALSE;
	}

	if ( !SetupPixelFormat() ) {
		::AfxMessageBox("SetupPixelFormat failed.\n");
		return FALSE;
	}

	if ( 0 == (m_hRC = ::wglCreateContext( m_pDC->GetSafeHdc() ) ) ) {
		::AfxMessageBox("wglCreateContext failed.");
		return FALSE;
	}

	if ( FALSE == ::wglMakeCurrent( m_pDC->GetSafeHdc(), m_hRC ) ) {
		::AfxMessageBox("wglMakeCurrent failed.");
		return FALSE;
	}

	// specify black as clear color
	::glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	// specify the back of the buffer as clear depth (0 closest, 1 farmost)
	::glClearDepth( 1.0f );
	// enable depth testing (Enable zbuffer - hidden surface removal)
	::glEnable( GL_DEPTH_TEST );
	// Set default black as background color.
	::glClearColor(0.0, 0.0, 0.0, 1.0f);
	// Set wireframe mode
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	// Enable auto-normalize of vertex normals
	glEnable(GL_NORMALIZE);
	// Enable alpha-blending
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// The code expects only the 2nd frame in the projection matrix to be used and the
	// first one to always be the identity matrix, so make sure this is the case
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	// The modelview matrix stack is arranged as follows:
	// === Current+Applied Transformations ========
	// ==== Applied Transformations ===============
	// ============ Identity ======================
	//                 ...
	glPushMatrix();
	glPushMatrix();

	return TRUE;
}



BOOL COpenGLView::SetupPixelFormat(PIXELFORMATDESCRIPTOR* pPFD)
{
	// default pixel format for a single-buffered,
	// OpenGL-supporting, hardware-accelerated, 
	// RGBA-mode format. Pass in a pointer to a different
	// pixel format if you want something else
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),// size of this pfd
		1,                      // version number
		PFD_DRAW_TO_WINDOW |    // support window
		PFD_SUPPORT_OPENGL |  // support OpenGL
		PFD_DOUBLEBUFFER,     // double buffered
		PFD_TYPE_RGBA,          // RGBA type
		24,                     // 24-bit color depth
		0, 0, 0, 0, 0, 0,       // color bits ignored
		0,                      // no alpha buffer
		0,                      // shift bit ignored
		0,                      // no accumulation buffer
		0, 0, 0, 0,             // accum bits ignored
		16,                     // 16-bit z-buffer
		0,                      // no stencil buffer
		0,                      // no auxiliary buffer
		PFD_MAIN_PLANE,         // main layer
		0,                      // reserved
		0, 0, 0                 // layer masks ignored
	};

	int pixelformat;
	PIXELFORMATDESCRIPTOR* pPFDtoUse;

	// let the user override the default pixel format
	pPFDtoUse = (0 == pPFD)? &pfd : pPFD; 

	if ( 0 == (pixelformat = ::ChoosePixelFormat( m_pDC->GetSafeHdc(), pPFDtoUse )) ) {
		::AfxMessageBox("ChoosePixelFormat failed.");
		return FALSE;
	}

	if ( FALSE == ::SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, pPFDtoUse ) ) {
		::AfxMessageBox("SetPixelFormat failed.");
		return FALSE;
	}

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COpenGLView message handlers


void COpenGLView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	if ( 0 >= cx || 0 >= cy ) {
		return;
	}

	// save the width and height of the current window
	m_WindowWidth = cx;
	m_WindowHeight = cy;

	// compute the aspect ratio
	// this will keep all dimension scales equal
	m_AspectRatio = (GLdouble)m_WindowWidth/(GLdouble)m_WindowHeight;

	// Now, set up the viewing area-select the full client area
	::glViewport(0, 0, m_WindowWidth, m_WindowHeight);

	if ( GL_NO_ERROR != ::glGetError() ) {
		::AfxMessageBox("Error while trying to set viewport.");
	}

	// select the viewing volume. You do it after you
	// get the aspect ratio and set the viewport
	if ( !SetupCamera() )
	{
		::AfxMessageBox("Error while trying to setup camera.");
		return;
	}

	// now select the modelview matrix and clear it
	// this is the mode we do most of our calculations in
	// so we leave it as the default mode.
	//::glMatrixMode(GL_MODELVIEW);
	//::glLoadIdentity();
	// TODO: DO WE WANT TO RESET THE TRANSFORMATIONS WHEN CHANGING VIEWING MODE?
}


BOOL COpenGLView::SetupViewingFrustum(void)
{
	// select a default perspective viewing volumn
	::gluPerspective( c_humanYFov, m_AspectRatio, this->m_zNear, this->m_zFar );

	// NOTE: Other commands you could have here are
	// glFrustum, which gives you much more control over
	// the perspective view, or glOrtho which is used for
	// parallel projections. No matter what you use, check
	// the error status when you set the viewing frustum!

	int e = ::glGetError();
	if ( e != GL_NO_ERROR ) {
		CString msg;
		msg.Format("Error at %d while trying to set viewing frustum: %x", __LINE__, e);
		::AfxMessageBox(msg);
		return FALSE;
	}

	return TRUE;
}


// This viewing projection gives us a constant aspect ration. This is done by
// increasing the corresponding size of the ortho cube.
BOOL COpenGLView::SetupViewingOrthoConstAspect(void)
{
	double windowSize = 4;	// the size of the window in GL coord system.

	if ( m_AspectRatio > 1 ) {	// x is bigger than y.
		// Maintain y size and increase x size (and z) accordingly
		// by MULTIPLYING by the aspect ratio.

		::glOrtho(  -windowSize*m_AspectRatio/2.0, windowSize*m_AspectRatio/2.0,
			-windowSize/2.0, windowSize/2.0, this->m_zNear, this->m_zFar);
	} else {
		// Maintain x size and increase y size (and z) accordingly, 
		// by DIVIDING the aspect Ration (because it's smaller than 1).

		::glOrtho(  -windowSize/2.0, windowSize/2.0,
			-windowSize/m_AspectRatio/2.0, windowSize/m_AspectRatio/2.0,
			this->m_zNear, this->m_zFar);
	}

	int e = ::glGetError();
	if ( e != GL_NO_ERROR ) {
		CString msg;
		msg.Format("Error at %d while trying to set viewing frustum: %x", __LINE__, e);
		::AfxMessageBox(msg);
		return FALSE;
	}

	return TRUE;
}





BOOL COpenGLView::OnEraseBkgnd(CDC* pDC) 
{
	// Windows will clear the window with the background color every time your window 
	// is redrawn, and then OpenGL will clear the viewport with its own background color.

	// return CView::OnEraseBkgnd(pDC);
	return true;
}



/////////////////////////////////////////////////////////////////////////////
// COpenGLView drawing
/////////////////////////////////////////////////////////////////////////////

void COpenGLView::OnDraw(CDC* pDC)
{
	COpenGLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// Light
	setupLightInScene();
	m_fogFarams.setupFog();
	m_materialManager.setupMaterialInScene();

	// Shading
	if (m_nLightShading == ID_LIGHT_SHADING_FLAT){
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		glShadeModel (GL_FLAT);
	}
	else if (m_nLightShading == ID_LIGHT_SHADING_GOURAUD){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
		glShadeModel (GL_SMOOTH);
	}
	else if (m_nLightShading == ID_SHADING_WIREFRAME){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}


	// Culling
	if (m_showBackFaces){
		glDisable(GL_CULL_FACE);
	}
	else{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}

	glClearColor((GLclampf)m_backgroundColor[0], (GLclampf)m_backgroundColor[1], (GLclampf)m_backgroundColor[2], 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// clear screen and zbuffer

	if (objectData == NULL)
	{
		// draw just the axis
		glPushMatrix();
		draw_axis();
		glPopMatrix();
	} 
	else
	{
		glPushMatrix();   
		RenderScene();
		if (torchEnabled)
		{
			// draw a red point marking the center of the torch
			glColor3d(1.0, 0.0, 0.0);
			glBegin(GL_POINTS);
				glVertex3d(cursor_x, cursor_y, cursor_z);
			glEnd();
		}
		glPopMatrix();
	}

	glFlush();
	SwapBuffers(wglGetCurrentDC());
}


/////////////////////////////////////////////////////////////////////////////
// COpenGLView OpenGL Finishing and clearing...

void COpenGLView::OnDestroy() 
{
	CView::OnDestroy();

	// this call makes the current RC not current
	if ( FALSE ==  ::wglMakeCurrent( 0, 0 ) ) {
		::AfxMessageBox("wglMakeCurrent failed.");
	}

	// delete the RC
	if ( m_hRC && (FALSE == ::wglDeleteContext( m_hRC )) ) {
		::AfxMessageBox("wglDeleteContext failed.");
	}

	// delete the DC
	if ( m_pDC ) {
		delete m_pDC;
	}
}



/////////////////////////////////////////////////////////////////////////////
// User Defined Functions


void COpenGLView::draw_axis()
{
	glLineWidth(2.0f);
	glColor3f(1.0f, 1.0f, 1.0f);

	glTranslatef(-0.5, -0.5, -0.5);

	// Draw Axis x
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3d(-0.1,0,0);
	glVertex3d(   1,0,0);
	glEnd();
	glPushMatrix();
	glTranslatef( 1.0f, 0.0f, 0.0f );
	glRotatef( 90.0, 0.0f, 1.0f, 0.0f );
	auxSolidCone(0.05,0.5);
	glPopMatrix();


	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex3d(0,-0.1,0);
	glVertex3d(0,   1,0);
	glEnd();
	glPushMatrix();
	glTranslatef( 0.0f, 1.0f, 0.0f );
	glRotatef( -90.0, 1.0f, 0.0f, 0.0f );
	auxSolidCone(0.05,0.5);
	glPopMatrix();


	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3d(0,0,-0.1);
	glVertex3d(0,0,   1);
	glEnd();
	glPushMatrix();
	glTranslatef( 0.0f, 0.0f, 1.0f );
	auxSolidCone(0.05,0.5);
	glPopMatrix();

	glLineWidth(1);			// return defaul line width


	glColor3f(1,1,1);		// return default color
}


void COpenGLView::RenderScene() {
	
	if (objectData != NULL)
	{
		if (m_recompile)
		{
			objectData->recompileAll();
			m_recompile = false;
		}

		glCallList( objectData->GetDisplayList(MyCompositeObject::SELECT_OPAQUE) );
		glDepthMask(GL_FALSE);	// make z-buffer read-only for rendering transparent objects
		glCallList( objectData->GetDisplayList(MyCompositeObject::SELECT_TRANSPARENT) );
		glDepthMask(GL_TRUE);	// restore write permissions for z-buffer

		if (m_showVertexNormals || m_showFaceNormals) {
			glDisable(GL_LIGHTING);
			glColor3f(0, 1, 0);
			glCallList( objectData->GetNormalsDisplayList(m_showFaceNormals, m_showVertexNormals) );
		}

		if (m_showBoundingBox){
			glDisable(GL_LIGHTING);
			glColor3f(1, 0, 0);
			objectData->DrawBoundingBox();
		}
	}

	return;
}


void COpenGLView::OnFileLoad() 
{
	TCHAR szFilters[] = _T ("IRIT Data Files (*.itd)|*.itd|All Files (*.*)|*.*||");

	CFileDialog dlg(TRUE, "itd", "*.itd", OFN_FILEMUSTEXIST | OFN_HIDEREADONLY ,szFilters);

	if (dlg.DoModal () == IDOK) {
		delete objectData;
		objectData = new MyCompositeObject();

		m_strItdFileName = dlg.GetPathName();		// Full path and filename
		int sep = m_strItdFileName.ReverseFind('\\');
		if (sep >= 0) {
			// last path-separator found
			CString filePath = m_strItdFileName.Left(sep);
			MyTextureManager::m_textureDir = filePath;
		}

		PngWrapper p;

		CGSkelProcessIritDataFiles(m_strItdFileName, 1);	// Open the file and read it.

		this->GetDocument()->SetTitle(m_strItdFileName);	// display the loaded file name in the title bar

		OnFileReset();
		materialReset();

		// mark for re-compilation
		m_recompile = true;
		setTesselation(false);
	} 
}





// VIEW HANDLERS ///////////////////////////////////////////

// Note: that all the following Message Handlers act in a similar way.
// Each control or command has two functions associated with it.

void COpenGLView::OnViewOrthographic() 
{
	m_nView = ID_VIEW_ORTHOGRAPHIC;
	m_bIsPerspective = false;

	if ( !SetupCamera() )
	{
		::AfxMessageBox("Error while trying to setup camera.");
	}
	Invalidate();		// redraw using the new view.
}

void COpenGLView::OnUpdateViewOrthographic(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nView == ID_VIEW_ORTHOGRAPHIC);
}

void COpenGLView::OnViewPerspective() 
{
	m_nView = ID_VIEW_PERSPECTIVE;
	m_bIsPerspective = true;

	if ( !SetupCamera() )
	{
		::AfxMessageBox("Error while trying to setup camera.");
	}
	Invalidate();
}

void COpenGLView::OnUpdateViewPerspective(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nView == ID_VIEW_PERSPECTIVE);
}




// ACTION HANDLERS ///////////////////////////////////////////

void COpenGLView::OnActionObjectspace()
{
	m_nSpace = ID_ACTION_OBJECTSPACE;
}

void COpenGLView::OnUpdateActionObjectspace(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nSpace == ID_ACTION_OBJECTSPACE);
}

void COpenGLView::OnActionViewspace()
{
	m_nSpace = ID_ACTION_VIEWSPACE;
}

void COpenGLView::OnUpdateActionViewspace(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nSpace == ID_ACTION_VIEWSPACE);
}

void COpenGLView::OnActionTexturetransformations()
{
	m_nSpace = ID_ACTION_TEXTURETRANSFORMATIONS;
}

void COpenGLView::OnUpdateActionTexturetransformations(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nSpace == ID_ACTION_TEXTURETRANSFORMATIONS);
}

void COpenGLView::OnActionRotate() 
{
	m_nAction = ID_ACTION_ROTATE;
}

void COpenGLView::OnUpdateActionRotate(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nAction == ID_ACTION_ROTATE);
}

void COpenGLView::OnActionTranslate() 
{
	m_nAction = ID_ACTION_TRANSLATE;
}

void COpenGLView::OnUpdateActionTranslate(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nAction == ID_ACTION_TRANSLATE);
}

void COpenGLView::OnActionScale() 
{
	m_nAction = ID_ACTION_SCALE;
}

void COpenGLView::OnUpdateActionScale(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nAction == ID_ACTION_SCALE);
}

void COpenGLView::OnActionUniformscaling()
{
	m_nAction = ID_ACTION_UNIFORMSCALING;
}

void COpenGLView::OnUpdateActionUniformscaling(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nAction == ID_ACTION_UNIFORMSCALING);
}



// AXIS HANDLERS ///////////////////////////////////////////


// Gets calles when the X button is pressed or when the Axis->X menu is selected.
// The only thing we do here is set the ChildView member variable m_nAxis to the 
// selected axis.
void COpenGLView::OnAxisX() 
{
	m_nAxis = ID_AXIS_X;
}

// Gets called when windows has to repaint either the X button or the Axis pop up menu.
// The control is responsible for its redrawing.
// It sets itself disabled when the action is a Scale action.
// It sets itself Checked if the current axis is the X axis.
void COpenGLView::OnUpdateAxisX(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nAxis == ID_AXIS_X);
}


void COpenGLView::OnAxisY() 
{
	m_nAxis = ID_AXIS_Y;
}

void COpenGLView::OnUpdateAxisY(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nAxis == ID_AXIS_Y);
}


void COpenGLView::OnAxisZ() 
{
	m_nAxis = ID_AXIS_Z;
}

void COpenGLView::OnUpdateAxisZ(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nAxis == ID_AXIS_Z);
}

void COpenGLView::OnAxisXy()
{
	m_nAxis = ID_AXIS_XY;
}

void COpenGLView::OnUpdateAxisXy(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nAxis == ID_AXIS_XY);
}


// OPTIONS HANDLERS ///////////////////////////////////////////




// LIGHT SHADING HANDLERS ///////////////////////////////////////////

void COpenGLView::OnLightShadingFlat() 
{
	m_nLightShading = ID_LIGHT_SHADING_FLAT;
	Invalidate();
}

void COpenGLView::OnUpdateLightShadingFlat(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nLightShading == ID_LIGHT_SHADING_FLAT);
}


void COpenGLView::OnLightShadingGouraud() 
{
	m_nLightShading = ID_LIGHT_SHADING_GOURAUD;
	Invalidate();
}

void COpenGLView::OnUpdateLightShadingGouraud(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nLightShading == ID_LIGHT_SHADING_GOURAUD);
}


void COpenGLView::OnShadingWireframe()
{
	m_nLightShading = ID_SHADING_WIREFRAME;
	Invalidate();
}

void COpenGLView::OnUpdateShadingWireframe(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nLightShading == ID_SHADING_WIREFRAME);
}

void COpenGLView::OnOptionsBackfacesculling()
{
	m_showBackFaces = !m_showBackFaces;
	Invalidate();
}

void COpenGLView::OnUpdateOptionsBackfacesculling(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( !m_showBackFaces);
}

void COpenGLView::OnMaterialTesselation()
{
	m_showTesselation = !m_showTesselation;
	setTesselation(m_showTesselation);
	m_recompile = true;
	Invalidate();
}

void COpenGLView::OnUpdateMaterialTesselation(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_showTesselation);
}
// LIGHT SETUP HANDLER ///////////////////////////////////////////

void COpenGLView::OnLightConstants() 
{
	CLightDialog dlg;

	for (int id=LIGHT_ID_1;id<MAX_LIGHT;id++)
	{	    
	    dlg.SetDialogData((LightID)id,m_lights[id]);
	}
	dlg.SetDialogData(LIGHT_ID_AMBIENT,m_ambientLight);

	if (dlg.DoModal() == IDOK) 
	{
	    for (int id=LIGHT_ID_1;id<MAX_LIGHT;id++)
	    {
			m_lights[id] = dlg.GetDialogData((LightID)id);
	    }
	    m_ambientLight = dlg.GetDialogData(LIGHT_ID_AMBIENT);
	}	
	Invalidate();
}

void COpenGLView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_LastTransformPoint = point;
}

void COpenGLView::OnLButtonUp(UINT nFlags, CPoint point)
{
	ApplyLatestTransform();
}

void COpenGLView::OnMouseMove(UINT nFlags, CPoint point)
{
	bool mustRedraw = false;

	if (torchEnabled && objectData != NULL)
	{
		// move torch
		static const double scale_factor = 1;

		SHORT s = GetKeyState(VK_CONTROL);
		if ( GetKeyState(VK_CONTROL) & (1 << (sizeof(SHORT)*CHAR_BIT)) )
		{
			// check if CTRL is down to decide whether to move the torch on Z-axis or not
			CPoint point;
			GetCursorPos(&point);	// GetCursorPos seems to return different coordinates than OnMouseMove,
									// so we override the point parameter for this part of the code so we
									// can compare the coordinates and get a correct result

			m_mouseScreenZ = 
				(m_prevMouseScreenZ + (point.y - m_lastCtrlPoint.y)/(m_WindowHeight*scale_factor)) * (m_mouseSensitivity / 100.0);
		}

		double	modelMatrix[16],
				projMatrix[16];
		int viewportMatrix[4];

		glGetDoublev(GL_MODELVIEW_MATRIX, &modelMatrix[0]);
		glGetDoublev(GL_PROJECTION_MATRIX, &projMatrix[0]);
		glGetIntegerv(GL_VIEWPORT, &viewportMatrix[0]);

		// keep in mind that object-space y-coordinates go from top-to-bottom and screen-space y-coordinates
		// go in the reverse direction
		gluUnProject(	point.x, m_WindowHeight-point.y, m_mouseScreenZ,
						modelMatrix, projMatrix, viewportMatrix,
						&cursor_x, &cursor_y, &cursor_z		);

		mustRedraw = true;
	}

	if (nFlags & MK_LBUTTON)
	{
		int	x_move_amt = (point.x - m_LastTransformPoint.x),
			y_move_amt = (m_LastTransformPoint.y - point.y );

		//x_move_amt *= m_mouseSensitivity / 100.0;
		//y_move_amt *= m_mouseSensitivity / 100.0;

		// undo the previously applied transformation - we'll reapply it now along with the
		// transform caused by this latest mouse move
		glPopMatrix();
		glPushMatrix();
		
		if (m_nSpace == ID_ACTION_TEXTURETRANSFORMATIONS)
		{
			glMatrixMode(GL_TEXTURE);
		}
		switch (m_nAction)
		{
		case ID_ACTION_ROTATE:
			RotateModel(x_move_amt, y_move_amt);
			break;
		case ID_ACTION_TRANSLATE:
			TranslateModel(x_move_amt, y_move_amt);
			break;
		case ID_ACTION_SCALE:
		case ID_ACTION_UNIFORMSCALING:
			ScaleModel(x_move_amt, y_move_amt);
			break;
		default:
			AfxMessageBox("Action not implemented.");
			break;
		}

		glMatrixMode(GL_MODELVIEW);
		mustRedraw = true;
	}

	if (mustRedraw)
		Invalidate();
}

void COpenGLView::TranslateModel(int x_amt, int y_amt)
{
	double factor = 1.0 * (m_mouseSensitivity/100.0 * 2.0);
	double x_translate, y_translate, z_translate;
	MouseDelta2ObjectDelta(x_amt, y_amt, &x_translate, &y_translate, &z_translate);
	x_translate = (m_nAxis == ID_AXIS_X || m_nAxis == ID_AXIS_XY)  ? x_translate*factor  : 0;
	y_translate = (m_nAxis == ID_AXIS_Y || m_nAxis == ID_AXIS_XY)  ? y_translate*factor  : 0;
	z_translate = (m_nAxis == ID_AXIS_Z)  ? z_translate*factor  : 0;

	if (m_nSpace == ID_ACTION_OBJECTSPACE || m_nSpace == ID_ACTION_TEXTURETRANSFORMATIONS)
		glTranslated(x_translate, y_translate, z_translate);
	else
	{
		// view-space transformation
		GLdouble currentMatrix[16];
		glGetDoublev(GL_MODELVIEW_MATRIX, &currentMatrix[0]);
		glLoadIdentity();
		glTranslated(x_translate, y_translate, z_translate);
		glMultMatrixd(&currentMatrix[0]);
	}
}

void COpenGLView::RotateModel(int x_amt, int y_amt)
{
	double rotate_axis_x, rotate_axis_y, rotate_axis_z;
	double rotate_amt;

	double factor = 2.0 * (m_mouseSensitivity/100.0 * 2.0);
	static const double xy_balance = 10.0;
	
	switch (m_nAxis)
	{
	case ID_AXIS_X:
		rotate_amt = (-y_amt*factor/m_WindowWidth) * 360;
		rotate_axis_x = 1.0;
		rotate_axis_y = rotate_axis_z = 0;
		break;
	case ID_AXIS_Y:
		rotate_amt = (x_amt*factor/m_WindowHeight) * 360;
		rotate_axis_y = 1.0;
		rotate_axis_x = rotate_axis_z = 0;
		break;
	case ID_AXIS_Z:
		rotate_amt = (x_amt*factor/m_WindowHeight) * 360;
		rotate_axis_z = 1.0;
		rotate_axis_x = rotate_axis_y = 0;
		break;
	case ID_AXIS_XY:
		rotate_amt = (x_amt*factor/m_WindowWidth + y_amt*factor/m_WindowHeight) * 180;
		rotate_axis_z = 0;
		rotate_axis_x = -1.0;
		rotate_axis_y = 1.0;
		break;
	}

	if (m_nSpace == ID_ACTION_OBJECTSPACE || m_nSpace == ID_ACTION_TEXTURETRANSFORMATIONS)
		glRotated(rotate_amt, rotate_axis_x, rotate_axis_y, rotate_axis_z);
	else
	{
		// view-space transformation
		GLdouble currentMatrix[16];
		glGetDoublev(GL_MODELVIEW_MATRIX, &currentMatrix[0]);

		const double cp[4] = {0, 0, 0, 1.0};
		double	cp1[4] = {0};

		// find the current projected axes origin
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				cp1[i] += cp[j] * currentMatrix[i + 4*j];
		for (int i = 0; i < 4; i++) cp1[i] /= cp1[3];

		glLoadIdentity();
		glRotated(rotate_amt, rotate_axis_x, rotate_axis_y, rotate_axis_z);
		glMultMatrixd(&currentMatrix[0]);

		double cp2[4] = {0};

		// find the new projected axes origin
		glGetDoublev(GL_MODELVIEW_MATRIX, &currentMatrix[0]);
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				cp2[i] += cp[j] * currentMatrix[i + 4*j];
		for (int i = 0; i < 4; i++) cp2[i] /= cp2[3];

		/*	figure out how much the object has moved as the result of the rotation about
			the axis, and move it the same amount in the other direction -- in viewspace
			coordinates! this is so the object rotates in viewspace coordinates but remains
			centered in the viewport */
		glLoadIdentity();
		glTranslated(cp1[0] - cp2[0], cp1[1] - cp2[1], cp1[2] - cp2[2]);
		glMultMatrixd(&currentMatrix[0]);
	}
}


void COpenGLView::ScaleModel(int x_amt, int y_amt)
{
	double factor = 1.0 * (m_mouseSensitivity/100.0 * 2.0);
	double	x_scale = 1 + (x_amt*factor / m_WindowWidth),
			y_scale = 1 + (y_amt*factor / m_WindowHeight),
			z_scale = y_scale;

	if (m_nAction == ID_ACTION_UNIFORMSCALING) {
		x_scale = y_scale = z_scale = (x_scale + y_scale)/2;
	} else {
		x_scale = (m_nAxis == ID_AXIS_X || m_nAxis == ID_AXIS_XY)  ? x_scale  : 1.0;
		y_scale = (m_nAxis == ID_AXIS_Y || m_nAxis == ID_AXIS_XY)  ? y_scale  : 1.0;
		z_scale = (m_nAxis == ID_AXIS_Z)  ? z_scale  : 1.0;
	}

	if (m_nSpace == ID_ACTION_OBJECTSPACE || m_nSpace == ID_ACTION_TEXTURETRANSFORMATIONS)
		glScaled(x_scale, y_scale, z_scale);
	else
	{
		// view-space transformation
		GLdouble currentMatrix[16];
		glGetDoublev(GL_MODELVIEW_MATRIX, &currentMatrix[0]);
		glLoadIdentity();
		glScaled(x_scale, y_scale, z_scale);
		glMultMatrixd(&currentMatrix[0]);
	}
}

bool COpenGLView::SetupCamera(bool resetTransforms)
{
	// define near + far planes
	this->m_zNear = 0.1,
	this->m_zFar = 20.0;
	
	if (objectData != NULL)
	{
		// near clipping plane is 10 times the size of the object
		// this should give us plenty of room to back away until it clips
		//this->m_zFar = objectData->bbox.zSize() * 10;
		this->m_zFar = 100*(objectData->bbox.xSize() + objectData->bbox.ySize() + objectData->bbox.zSize());
	}

	bool ret;

	/**	We want to perform all camera manipulations the same for both viewing modes.
		If we setup perspective projection here, the scaling calculation later on will
		be incorrect. Therefore, we setup orthographic projection and later fix the
		projection matrix if this is incorrect.
	**/
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPushMatrix();		// restore identity matrix
	ret = SetupViewingOrthoConstAspect();
	glMatrixMode(GL_MODELVIEW);

	if (!ret)
		return ret;

	if (resetTransforms)
	{
		glPopMatrix();
		glPopMatrix();	// reset to identity matrix
		glPushMatrix();
		glPushMatrix();

		if (objectData != NULL)
		{
			// scale the model so it fits on  about 3/4 of the screen in orthographic view
			// we fix the distortion this creates in perspective view later with a translation
			// down the Z axis
			
			double	modelMatrix[16],
					projMatrix[16];
			int viewportMatrix[4];

			double w_xmin, w_xmax, w_ymin, w_ymax, w_zmin, w_zmax;

			glGetDoublev(GL_MODELVIEW_MATRIX, &modelMatrix[0]);
			glGetDoublev(GL_PROJECTION_MATRIX, &projMatrix[0]);
			glGetIntegerv(GL_VIEWPORT, &viewportMatrix[0]);
			
			gluProject(	objectData->bbox.x_min, objectData->bbox.y_min, objectData->bbox.z_min,
						modelMatrix, projMatrix, viewportMatrix, &w_xmin, &w_ymin, &w_zmin);
			gluProject(	objectData->bbox.x_max, objectData->bbox.y_max, objectData->bbox.z_max,
						modelMatrix, projMatrix, viewportMatrix, &w_xmax, &w_ymax, &w_zmax);

			MyBoundingBox w_bbox(w_xmin, w_xmax, w_ymin, w_ymax, w_zmin, w_zmax);

			double	x_scale = (m_WindowWidth * 3 / 4) / w_bbox.xSize(),
					y_scale = (m_WindowHeight * 3 / 4) / w_bbox.ySize(),
					scale = min(x_scale, y_scale);	// if we need to reduce the model then reduce by the maximum amount
													// if enlarging enlarge by the minimum amount

			glScaled(scale, scale, scale);
		}

		// calculate needed camera distance from object and move the camera
		// the calculation is meant for perspective mode, but it should work just as well for orthographic
		// mode, since all we need is to move the object far enough back so it doesn't clip with the near plane

		double distance = 3.0;	// default distance if no object is loaded (for the axes)

		if (objectData != NULL)
		{
			// we take this opportunity to also center the model in the window
			MyBoundingBox bbox = objectData->bbox;
			glTranslated( -bbox.GetCenterX(), -bbox.GetCenterY(), 0 );

			double radFovY_half = M_PI/360 * c_humanYFov;
			double	size_x = objectData->bbox.xSize(),
					size_y = max( objectData->bbox.ySize(), size_x/m_AspectRatio );

			distance = (0.5*size_y) / std::sin(radFovY_half);
			distance += objectData->bbox.zSize();	// don't forget the object isn't flat...
		}

		// get the size of the object (either loaded model or default axes) in the z plane
		double zSize = (objectData != NULL) ? objectData->bbox.zSize() : 2;

		if (distance <= this->m_zNear + zSize)
			// the object is clipping the near plane!
			distance = this->m_zNear + zSize;
		
		if (distance + zSize >= this->m_zFar)
			// we're moving it past the far plane!
			distance = this->m_zFar - zSize - 1;

		// move the camera
		glTranslated(0.0, 0.0, -distance);

		ApplyLatestTransform();	// apply this _NOT JUST_ for current transformation but to the ones to follow as well
	}

	/**	If we should be in projection mode fix it now! **/
	if (m_bIsPerspective) {
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glPushMatrix();		// restore identity matrix
		ret = SetupViewingFrustum();
		glMatrixMode(GL_MODELVIEW);
	}

	if (!ret)
		return ret;

	if ( GL_NO_ERROR != ::glGetError() ) {
		::AfxMessageBox("Error while trying to set camera position.");
		return FALSE;
	}

	return TRUE;
}

void COpenGLView::OnOptionsMousesensitivity()
{
	CMouseSensitivityDialog dlg(m_mouseSensitivity);

	if (dlg.DoModal () == IDOK) {
		m_mouseSensitivity = dlg.m_sensitivity;
	}
}

void COpenGLView::OnOptionsChangewirecolor()
{
	CColorDialog dlg;
	if (dlg.DoModal () == IDOK) {
		if(NULL != objectData){
			COLORREF color = dlg.GetColor();
			objectData->changeColor(	GetRValue(color) / 255.0,
										GetGValue(color) / 255.0,
										GetBValue(color) / 255.0	);

			// mark for re-compilation
			m_recompile = true;
		
			Invalidate();
		}
	}
}

void COpenGLView::OnOptionsChangebackgroundcolor()
{
	CColorDialog dlg;
	if (dlg.DoModal () == IDOK) {
			COLORREF color = dlg.GetColor();
			m_backgroundColor[0] = GetRValue(color) / 255.0;
			m_backgroundColor[1] = GetGValue(color) / 255.0;
			m_backgroundColor[2] = GetBValue(color) / 255.0;
			Invalidate();
	}
}

void COpenGLView::OnOptionsDrawboundingbox()
{
	m_showBoundingBox = !m_showBoundingBox;
	Invalidate();
}

void COpenGLView::OnUpdateOptionsDrawboundingbox(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_showBoundingBox);
}

void COpenGLView::OnOptionsShowverticesnormals()
{
	m_showVertexNormals = !m_showVertexNormals;
	Invalidate();
}

void COpenGLView::OnUpdateOptionsShowverticesnormals(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_showVertexNormals);
}

void COpenGLView::OnOptionsShowfacesnormals()
{
	m_showFaceNormals = !m_showFaceNormals;
	Invalidate();
}

void COpenGLView::OnUpdateOptionsShowfacesnormals(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_showFaceNormals);
}

void COpenGLView::OnOptionsPerspectivecontrol()
{
	AfxMessageBox("This option not implemented");
}

void COpenGLView::ApplyLatestTransform(void)
{
	GLdouble m[16];	
	glGetDoublev(GL_MODELVIEW_MATRIX, &m[0]);
	glPopMatrix();
	glLoadMatrixd(&m[0]);
	glPushMatrix();
}

void COpenGLView::OnOptionsTorch()
{
	static bool familiar = false;

	if (!familiar)
	{
		CString msg =	"This appears to be your first time using the\n"
						"torch feature. Move the mouse around the\n"
						"object to illuminate different parts of it.\n"
						"Hold the Ctrl key and drag the the mouse\n"
						"up and down to move the torch on the Z\n"
						"axis.";
		AfxMessageBox(msg, MB_OK|MB_ICONINFORMATION);
		familiar = true;
	}

	torchEnabled = !torchEnabled;
	Invalidate();
}

void COpenGLView::OnUpdateOptionsTorch(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(torchEnabled);
}

void COpenGLView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_CONTROL)
	{
		m_prevMouseScreenZ = m_mouseScreenZ;	// save it, since it's going to be getting changed now...
		GetCursorPos(&m_lastCtrlPoint);
	}
}

void COpenGLView::OnFileReset()
{
	if (objectData != NULL){
		m_backgroundColor[0] = m_backgroundColor[1] = m_backgroundColor[2] = 0;
		
		glMatrixMode(GL_TEXTURE);
		glPopMatrix();
		glPushMatrix();

		// reset the ModelView matrix
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glPopMatrix();
		glPushMatrix();
		glPushMatrix();

		SetupCamera(true);	// setup projection and camera position for the newly loaded model

		double objSize = max( objectData->bbox.xSize(), objectData->bbox.ySize() );
		objSize = max( objSize, objectData->bbox.zSize() );
		torch_range = objSize / 4;

		// set the "mouse z-coordinate" for the torch to coincide with the center of the object's
		// bounding-box, so we start off with it in the general area of the object...
		double	modelMatrix[16],
				projMatrix[16];
		int viewportMatrix[4];

		glGetDoublev(GL_MODELVIEW_MATRIX, &modelMatrix[0]);
		glGetDoublev(GL_PROJECTION_MATRIX, &projMatrix[0]);
		glGetIntegerv(GL_VIEWPORT, &viewportMatrix[0]);
		double tmp;

		gluProject(	objectData->bbox.GetCenterX(), objectData->bbox.GetCenterY(), objectData->bbox.GetCenterZ(),
					modelMatrix, projMatrix, viewportMatrix,
					&tmp, &tmp, &m_mouseScreenZ	);
	}

	Invalidate();	// force a WM_PAINT for drawing.
}

void COpenGLView::lightReset(){
	
	setupLightInScene();

	for (int id=LIGHT_ID_1;id<MAX_LIGHT;id++)
	{	    
		m_lights[id].reset();
	}
	m_lights[0].enabled = true;
	m_ambientLight.colorR = m_ambientLight.colorG = m_ambientLight.colorB = 0;
}



void COpenGLView::setupLightInScene(){

	//Enable view lights 
	GLdouble currentMatrix[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, &currentMatrix[0]);
	glLoadIdentity();

	m_lightManager.setupGeneralLight(	(!torchEnabled) && 
										(objectData != NULL) && 
										(m_nLightShading != ID_SHADING_WIREFRAME),
										m_ambientLight	);
	for (int i=0;i<MAX_LIGHT; i++ ){
		if (m_lights[i].space == LIGHT_SPACE_VIEW)
			m_lightManager.showLight(m_lights[i], i);
	}

	glMultMatrixd(&currentMatrix[0]);


	//Enable local lights 
	for (int i=0;i<MAX_LIGHT; i++ ){
		if (m_lights[i].space == LIGHT_SPACE_LOCAL)
			m_lightManager.showLight(m_lights[i], i);
	}	
}
void COpenGLView::OnMaterialLoadtexture()
{
	TCHAR szFilters[] = _T ("Png Files (*.png)|*.png|All Files (*.*)|*.*||");

	CFileDialog dlg(TRUE, "png", "*.png", OFN_FILEMUSTEXIST | OFN_HIDEREADONLY ,szFilters);

	if (dlg.DoModal () == IDOK) {
		std::string file(dlg.GetPathName());

		glMatrixMode(GL_TEXTURE);
		glPopMatrix();
		glPushMatrix();

		m_textureManager.addPTexture(file.c_str(), true);
		m_textureManager.set();

		for (int i=0; i<objectData->m_nextObj; i++){
			objectData->m_objects[i]->enableTexture(false);
		}

		m_recompile = true;
		Invalidate();
	}
}



void COpenGLView::OnLightFog()
{
	CFogDialog dlg(m_fogFarams);
	if (dlg.DoModal () == IDOK) {
		m_fogFarams = dlg.getFogParams();
		Invalidate();
	}
}

void COpenGLView::OnMaterialProperties()
{
	CMaterialDlg dlg(m_materialManager);
	if (dlg.DoModal () == IDOK) {
		m_materialManager = dlg.getMaterialManager();
		m_textureManager.setupTextureParams(m_materialManager);
		m_textureManager.set();

		for (int i = 0; i < objectData->m_nextObj; i++){
			objectData->m_objects[i]->m_textureManager.setupTextureParams(m_materialManager);
		}

		m_recompile = true;
		Invalidate();
	}
}

void COpenGLView::OnResetLight()
{
	lightReset();
	Invalidate();
}

void COpenGLView::OnResetView()
{
	OnFileReset();
}


void COpenGLView::materialReset(){
	m_materialManager.reset();
	m_textureManager.setupTextureParams(m_materialManager);
}


void COpenGLView::setTesselation(bool bTesselation){
	m_showTesselation = bTesselation;
		GLUtesselator* tobj = (GLUtesselator*)m_tesselationManager.setTesselation(bTesselation);
	if (objectData != NULL){
		for (int i = 0; i <  objectData->m_nextObj; i++) {
			objectData->m_objects[i]->setTesselator(tobj);
		}
	}
}


void COpenGLView::OnMaterialLoadmipmap()
{
	string *objectNames;
	int len;

	if (objectData) {
		len = objectData->m_nextObj;
		objectNames = new string[len];
		for (int i = 0; i < len; i++)
			objectNames[i] = objectData->m_objects[i]->m_name;
	} else {
		len = 0;
		objectNames = NULL;
	}

	LoadTextureDlg dlg(objectNames, len);

	if (dlg.DoModal() == IDOK) {
		if (!objectData) return;	// just in case...

		int obj = dlg.m_objSelected;
		string file = dlg.m_filePath;
		
		objectData->m_objects[obj]->m_textureManager.addPTexture(file.c_str(), true, true);
		m_recompile = true;
	}
}

/**	This helper function calculates how much an object should be transformed
	(translated, scaled) in object coordinates to match a given movement in
	screen coordinates. For consistency we calculate the projections using the
	following mouse location values:
	Before: screen.center.x, screen.center.y, object.center.z
	After: screen.center.x + dx, screen.center.y + dy, object.center.z
**/
void COpenGLView::MouseDelta2ObjectDelta(int dx, int dy, double* obj_dx, double* obj_dy, double* obj_dz)
{
	double	modelMatrix[16],
			projMatrix[16];
	int viewportMatrix[4];

	glGetDoublev(GL_MODELVIEW_MATRIX, &modelMatrix[0]);
	glGetDoublev(GL_PROJECTION_MATRIX, &projMatrix[0]);
	glGetIntegerv(GL_VIEWPORT, &viewportMatrix[0]);

	double	winx_before = m_WindowWidth/2,
			winy_before = m_WindowHeight/2,
			winz_before = 0,
			t;
	double	center[4] = {	(objectData) ? objectData->bbox.GetCenterX() : 0,
							(objectData) ? objectData->bbox.GetCenterY() : 0,
							(objectData) ? objectData->bbox.GetCenterZ() : 0,
							1.0													};

	// we need to apply the modelview and projection matrices to the center-point!
	

	ApplyMatrix(center, modelMatrix, true);

	// first convert object-z center to screen z-center
	gluProject(	center[0], center[1], center[2],
				modelMatrix, projMatrix, viewportMatrix,
				&t, &t, &winz_before);

	double objx_before, objy_before, objz_before;

	// calculate "BEFORE" coordinates
	if (!	gluUnProject(	winx_before, winy_before, winz_before,
							modelMatrix, projMatrix, viewportMatrix,
							&objx_before, &objy_before, &objz_before		)	)
		AfxMessageBox("Failed projecting BEFORE coordinates");

	double objx_after, objy_after, objz_after;

	// calculate "AFTER" coordinates
	if (!	gluUnProject(	winx_before + dx, winy_before + dy, winz_before,
							modelMatrix, projMatrix, viewportMatrix,
							&objx_after, &objy_after, &objz_after		)	)
		AfxMessageBox("Failed projecting AFTER coordinates");

	static const double factor = 0.3;	// heuristic
	*obj_dx = (objx_after - objx_before) * factor;
	*obj_dy = (objy_after - objy_before) * factor;
	*obj_dz = *obj_dy;
}

/**	Apply transformation matrix m to point vector v=(x,y,z,w). After the transformation v
	contains vM
**/
void COpenGLView::ApplyMatrix(double v[4], double m[16], bool normalize)
{
	double v_[4] = {0};

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			v_[i] += m[4*i + j] * v[j];

	if (normalize) {
		for (int i = 0; i < 4; i++)
			v_[i] /= v_[3];
	}

	// copy result
	for (int i = 0; i < 4; i++)
		v[i] = v_[i];
}
