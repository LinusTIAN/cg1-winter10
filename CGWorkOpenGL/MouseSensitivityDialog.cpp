// MouseSensitivityDialog.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGL.h"
#include "MouseSensitivityDialog.h"


// CMouseSensitivityDialog dialog

IMPLEMENT_DYNAMIC(CMouseSensitivityDialog, CDialog)

CMouseSensitivityDialog::CMouseSensitivityDialog(int sensivity,CWnd* pParent /*=NULL*/)
	: CDialog(CMouseSensitivityDialog::IDD, pParent)
	, m_sensitivity(sensivity)
{
}

CMouseSensitivityDialog::~CMouseSensitivityDialog()
{
}

void CMouseSensitivityDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_sensitivityCtrl);
	DDX_Slider(pDX, IDC_SLIDER1, m_sensitivity);
}


BOOL CMouseSensitivityDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_sensitivityCtrl.SetPos(m_sensitivity);
	return TRUE; 
}

BEGIN_MESSAGE_MAP(CMouseSensitivityDialog, CDialog)
END_MESSAGE_MAP()


// CMouseSensitivityDialog message handlers
