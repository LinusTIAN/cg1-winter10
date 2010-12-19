// FogDialog.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGL.h"
#include "FogDialog.h"


// CFogDialog dialog

IMPLEMENT_DYNAMIC(CFogDialog, CDialog)

CFogDialog::CFogDialog(MyFogPrameters &fogPrameters, CWnd* pParent /*=NULL*/)
	: CDialog(CFogDialog::IDD, pParent)
	, m_rColor(_T(""))
	, m_gColor(_T(""))
	, m_bColor(_T(""))
	, m_mode(_T(""))
	, m_density(_T(""))
	, m_enabled(FALSE)
{
	m_fogPrameters = fogPrameters;

	m_enabled = m_fogPrameters.enabled;
	
	CString chBuffer;
	chBuffer.Format( "%d", m_fogPrameters.m_r);
	m_rColor.SetString(chBuffer);
	chBuffer.Format( "%d", m_fogPrameters.m_g);
	m_gColor.SetString(chBuffer);
	chBuffer.Format( "%d", m_fogPrameters.m_b);
	m_bColor.SetString(chBuffer);
	
	chBuffer.Format( "%f", m_fogPrameters.m_density);
	m_density.SetString(chBuffer);

	switch(m_fogPrameters.m_type)
	{
	case FOG_GL_EXP:
		//m_mode.SetString("GL_EXP");
		break;
	case FOG_GL_EXP2:
		//m_mode.SetString("GL_EXP2");
		break;
	case FOG_GL_LINEAR:
		//m_mode.SetString("GL_LINEAR");
		break;
	}
}

CFogDialog::~CFogDialog()
{
}

void CFogDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_colorButton);
	DDX_Control(pDX, IDC_EDIT1, m_rColorCtrl);
	DDX_Control(pDX, IDC_EDIT2, m_gColorCtrl);
	DDX_Control(pDX, IDC_EDIT3, m_bColorCtrl);
	DDX_Text(pDX, IDC_EDIT1, m_rColor);
	DDX_Text(pDX, IDC_EDIT2, m_gColor);
	DDX_Text(pDX, IDC_EDIT3, m_bColor);
	DDX_Control(pDX, IDC_COMBO1, m_modeCtrl);
	DDX_CBString(pDX, IDC_COMBO1, m_mode);
	DDX_Control(pDX, IDC_EDIT4, m_densityCtrl);
	DDX_Text(pDX, IDC_EDIT4, m_density);
	DDX_Control(pDX, IDC_CHECK1, m_enabledCtrl);
	DDX_Check(pDX, IDC_CHECK1, m_enabled);
}


BEGIN_MESSAGE_MAP(CFogDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CFogDialog::OnBnClickedButton1)
END_MESSAGE_MAP()


BOOL CFogDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	//m_colorButton.setc

	return TRUE;
}

// CFogDialog message handlers

void CFogDialog::OnBnClickedButton1()
{
	CColorDialog dlg;
	if (dlg.DoModal () == IDOK) {
		COLORREF color = dlg.GetColor();
		
		CString chBuffer;
		int c = GetRValue(color) ;
		chBuffer.Format( "%d", c );		
		m_rColor.SetString(chBuffer);
		m_rColorCtrl.SetWindowTextA(m_rColor);

		c = GetGValue(color) ;
		chBuffer.Format( "%d", c);		
		m_gColor.SetString(chBuffer);
		m_gColorCtrl.SetWindowTextA(m_gColor);

		c = GetBValue(color) ;
		chBuffer.Format( "%d", c);		
		m_bColor.SetString(chBuffer);
		m_bColorCtrl.SetWindowTextA(m_bColor);

			
	}
}

MyFogPrameters& CFogDialog::getFogParams(){

	m_fogPrameters.enabled = m_enabled;

	if (m_rColor.Compare("") != 0)
		m_fogPrameters.m_r = atoi(m_rColor);
	if (m_gColor.Compare("") != 0)
		m_fogPrameters.m_g = atoi(m_gColor);
	if (m_bColor.Compare("") != 0)
		m_fogPrameters.m_b = atoi(m_bColor);
	
	if (m_density.Compare("") != 0)
		m_fogPrameters.m_density = atof(m_density);

	
	if (m_mode.Compare("GL_EXP") == 0)
		m_fogPrameters.m_type = FOG_GL_EXP;
	else if (m_mode.Compare("GL_EXP2") == 0)
		m_fogPrameters.m_type = FOG_GL_EXP2;
	else if (m_mode.Compare("GL_LINEAR") == 0)
		m_fogPrameters.m_type = FOG_GL_LINEAR;
	
	return m_fogPrameters;
}
