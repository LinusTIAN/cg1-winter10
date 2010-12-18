// PerspectiveOptionsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGL.h"
#include "PerspectiveOptionsDialog.h"


// CPerspectiveOptionsDialog dialog

IMPLEMENT_DYNAMIC(CPerspectiveOptionsDialog, CDialog)

CPerspectiveOptionsDialog::CPerspectiveOptionsDialog(int dVal, CWnd* pParent /*=NULL*/)
	: CDialog(CPerspectiveOptionsDialog::IDD, pParent)
	, m_dVal(_T(""))
{
	CString chBuffer;
    chBuffer.Format( "%d", dVal);
	m_dVal.SetString(chBuffer);
}

CPerspectiveOptionsDialog::~CPerspectiveOptionsDialog()
{
}

void CPerspectiveOptionsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_dCtl);
	DDX_Text(pDX, IDC_EDIT1, m_dVal);
}


BEGIN_MESSAGE_MAP(CPerspectiveOptionsDialog, CDialog)
END_MESSAGE_MAP()


// CPerspectiveOptionsDialog message handlers
