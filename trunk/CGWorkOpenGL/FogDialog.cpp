// FogDialog.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGL.h"
#include "FogDialog.h"


// CFogDialog dialog

IMPLEMENT_DYNAMIC(CFogDialog, CDialog)

CFogDialog::CFogDialog(MyFogPrameters &fogPrameters, CWnd* pParent /*=NULL*/)
	: CDialog(CFogDialog::IDD, pParent)
	, m_mode(_T(""))
	, m_enabled(fogPrameters.enabled)
{
	m_fogPrameters = fogPrameters;
	
	
	switch(m_fogPrameters.m_type)
	{
	case FOG_GL_EXP:
		m_mode.SetString("GL_EXP");
		break;
	case FOG_GL_EXP2:
		m_mode.SetString("GL_EXP2");
		break;
	case FOG_GL_LINEAR:
		m_mode.SetString("GL_LINEAR");
		break;
	}
}

CFogDialog::~CFogDialog()
{
}

void CFogDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_BUTTON1, m_colorButton);
	DDX_Text(pDX, IDC_EDIT1, m_fogPrameters.m_r);
	DDV_MinMaxInt(pDX, m_fogPrameters.m_r, 0, 255);
	DDX_Text(pDX, IDC_EDIT2, m_fogPrameters.m_g);
	DDV_MinMaxInt(pDX, m_fogPrameters.m_g, 0, 255);
	DDX_Text(pDX, IDC_EDIT3, m_fogPrameters.m_b);
	DDV_MinMaxInt(pDX, m_fogPrameters.m_b, 0, 255);

	DDX_Text(pDX, IDC_EDIT4, m_fogPrameters.m_density);
	DDV_MinMaxDouble(pDX, m_fogPrameters.m_density, 0, 1);

	DDX_CBString(pDX, IDC_COMBO1, m_mode);
	DDX_Check(pDX, IDC_CHECK1, m_enabled);
}


BEGIN_MESSAGE_MAP(CFogDialog, CDialog)
//	ON_BN_CLICKED(IDC_BUTTON1, &CFogDialog::OnBnClickedButton1)
END_MESSAGE_MAP()


BOOL CFogDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;
}

MyFogPrameters& CFogDialog::getFogParams(){

	m_fogPrameters.enabled = m_enabled;

	
	if (m_mode.Compare("GL_EXP") == 0)
		m_fogPrameters.m_type = FOG_GL_EXP;
	else if (m_mode.Compare("GL_EXP2") == 0)
		m_fogPrameters.m_type = FOG_GL_EXP2;
	else if (m_mode.Compare("GL_LINEAR") == 0)
		m_fogPrameters.m_type = FOG_GL_LINEAR;
	
	return m_fogPrameters;
}
