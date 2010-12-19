// OpenGLView.h : interface of the COpenGLView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENGLVIEW_H__5857316D_EA60_11D5_9FD5_00D0B718E2CD__INCLUDED_)
#define AFX_OPENGLVIEW_H__5857316D_EA60_11D5_9FD5_00D0B718E2CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "gl\gl.h"    // Include the standard OpenGL  headers
#include "gl\glu.h"   // Add the utility library


#include "Light.h"
#include "atltypes.h"
#include "MyTorchFX.h"
#include "MyLight.h"
#include "MyFogPrameters.h"
#include "MyMaterialManager.h"
#include "MyTextureManager.h"

/////////////////////////////////////////////////////////////////////////////////////////////
// #defined Constants
#define c_humanYFov		40.0	// constant that holds preset Y-FOV for human vision

class COpenGLView : public CView
{
protected: // create from serialization only
	COpenGLView();
	DECLARE_DYNCREATE(COpenGLView)

// Attributes
public:
	COpenGLDoc* GetDocument();

// Operations
public:

private:
	int m_nAxis;				// Axis of Action, X Y or Z
	int m_nAction;				// Rotate, Translate, Scale
	int m_nView;				// Orthographic, perspective
	int m_nSpace;				// Object/View-space/texture transform
	bool m_bIsPerspective;			// is the view perspective
	
	CString m_strItdFileName;		// file name of IRIT data

	int m_nLightShading;			// shading: Flat, Gouraud.

	LightParams m_lights[MAX_LIGHT];	//configurable lights array
	LightParams m_ambientLight;		//ambient light (only RGB is used)

	int m_mouseSensitivity;
	bool m_showBoundingBox;
	bool m_showVertexNormals;
	bool m_showFaceNormals;
	bool m_recompile;
	double m_backgroundColor[3];
	float m_dVal;
	MyFogPrameters m_fogFarams;
	MyMaterialManager m_materialManager;
	MyTextureManager m_textureManager;
	//MyTorchFX *m_torch;



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenGLView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COpenGLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL InitializeOpenGL();
	BOOL SetupPixelFormat(PIXELFORMATDESCRIPTOR* pPFD = 0); // the '= 0' was added.
	BOOL SetupViewingFrustum(void);
	BOOL SetupViewingOrthoConstAspect(void);

	virtual void RenderScene();


	HGLRC    m_hRC;			// holds the Rendering Context
	CDC*     m_pDC;			// holds the Device Context
	int m_WindowWidth;		// hold the windows width
	int m_WindowHeight;		// hold the windows height
	double m_AspectRatio;		// hold the fixed Aspect Ration
	double	m_zNear,
			m_zFar;		// hold the clipping planes
	MyLight m_lightManager;
	bool m_showBackFaces;

private:
	void draw_axis();
	void scaleAccordingToAxis(double scale_amt);
	void lightReset();
	void setupLightInScene();


// Generated message map functions
protected:
	//{{AFX_MSG(COpenGLView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFileLoad();
	afx_msg void OnViewOrthographic();
	afx_msg void OnUpdateViewOrthographic(CCmdUI* pCmdUI);
	afx_msg void OnViewPerspective();
	afx_msg void OnUpdateViewPerspective(CCmdUI* pCmdUI);
	afx_msg void OnActionRotate();
	afx_msg void OnUpdateActionRotate(CCmdUI* pCmdUI);
	afx_msg void OnActionScale();
	afx_msg void OnUpdateActionScale(CCmdUI* pCmdUI);
	afx_msg void OnActionTranslate();
	afx_msg void OnUpdateActionTranslate(CCmdUI* pCmdUI);
	afx_msg void OnAxisX();
	afx_msg void OnUpdateAxisX(CCmdUI* pCmdUI);
	afx_msg void OnAxisY();
	afx_msg void OnUpdateAxisY(CCmdUI* pCmdUI);
	afx_msg void OnAxisZ();
	afx_msg void OnUpdateAxisZ(CCmdUI* pCmdUI);
	afx_msg void OnLightShadingFlat();
	afx_msg void OnUpdateLightShadingFlat(CCmdUI* pCmdUI);
	afx_msg void OnLightShadingGouraud();
	afx_msg void OnUpdateLightShadingGouraud(CCmdUI* pCmdUI);
	afx_msg void OnLightConstants();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CPoint m_LastTransformPoint;
	CPoint m_lastCtrlPoint;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	void TranslateModel(double x_amt, double y_amt);
	void RotateModel(double x_amt, double y_amt);
	void ScaleModel(double x_amt, double y_amt);
public:
	afx_msg void OnActionObjectspace();
	afx_msg void OnUpdateActionObjectspace(CCmdUI *pCmdUI);
	afx_msg void OnActionViewspace();
	afx_msg void OnUpdateActionViewspace(CCmdUI *pCmdUI);
	bool SetupCamera(bool resetTransforms = false);
	afx_msg void OnOptionsMousesensitivity();
	afx_msg void OnOptionsChangewirecolor();
	afx_msg void OnOptionsChangebackgroundcolor();
	afx_msg void OnOptionsDrawboundingbox();
	afx_msg void OnUpdateOptionsDrawboundingbox(CCmdUI *pCmdUI);
	afx_msg void OnOptionsShowverticesnormals();
	afx_msg void OnUpdateOptionsShowverticesnormals(CCmdUI *pCmdUI);
	afx_msg void OnOptionsShowfacesnormals();
	afx_msg void OnUpdateOptionsShowfacesnormals(CCmdUI *pCmdUI);
	afx_msg void OnOptionsPerspectivecontrol();

protected:
	// call this function to apply the latest transformation along with the rest of them -
	// use this when the transformation is large enough or when we need to apply it to
	// be able to do something else. When the left mouse button is released from dragging
	// might be a good time to call this...
	void ApplyLatestTransform(void);
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnOptionsTorch();
	afx_msg void OnUpdateOptionsTorch(CCmdUI *pCmdUI);
	double m_mouseScreenZ, m_prevMouseScreenZ;
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnAxisXy();
	afx_msg void OnUpdateAxisXy(CCmdUI *pCmdUI);
	afx_msg void OnFileReset();
	afx_msg void OnActionUniformscaling();
	afx_msg void OnUpdateActionUniformscaling(CCmdUI *pCmdUI);
	afx_msg void OnShadingWireframe();
	afx_msg void OnUpdateShadingWireframe(CCmdUI *pCmdUI);
	afx_msg void OnMaterialLoadtexture();
	afx_msg void OnOptionsBackfacesculling();
	afx_msg void OnUpdateOptionsBackfacesculling(CCmdUI *pCmdUI);
	afx_msg void OnLightFog();
	afx_msg void OnMaterialProperties();
	afx_msg void OnActionTexturetransformations();
	afx_msg void OnUpdateActionTexturetransformations(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in OpenGLView.cpp
inline COpenGLDoc* COpenGLView::GetDocument()
   { return (COpenGLDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENGLVIEW_H__5857316D_EA60_11D5_9FD5_00D0B718E2CD__INCLUDED_)
