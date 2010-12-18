// MouseSensivityDialog.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGL.h"
#include "MouseSensivityDialog.h"


// CMouseSensivityDialog dialog

IMPLEMENT_DYNAMIC(CMouseSensivityDialog, CDialog)

CMouseSensivityDialog::CMouseSensivityDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMouseSensivityDialog::IDD, pParent)
{

}

CMouseSensivityDialog::~CMouseSensivityDialog()
{
}

void CMouseSensivityDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMouseSensivityDialog, CDialog)
END_MESSAGE_MAP()


// CMouseSensivityDialog message handlers
