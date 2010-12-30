// LoadTextureDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGL.h"
#include "LoadTextureDlg.h"


// LoadTextureDlg dialog

IMPLEMENT_DYNAMIC(LoadTextureDlg, CDialog)

LoadTextureDlg::LoadTextureDlg(string *objNames, int len, CWnd* pParent /*=NULL*/)
	: CDialog(LoadTextureDlg::IDD, pParent)
	, m_filePath(_T(""))
	, m_objSelected(0)
{
	m_objNames = objNames;
	m_nNames = len;
}

LoadTextureDlg::~LoadTextureDlg()
{
}

void LoadTextureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OBJSELECT, m_objectCombo);
	DDX_Text(pDX, IDC_FILENAME, m_filePath);
}


BEGIN_MESSAGE_MAP(LoadTextureDlg, CDialog)
	ON_BN_CLICKED(IDC_BROWSE, &LoadTextureDlg::OnBnClickedBrowse)
	ON_CBN_SELCHANGE(IDC_OBJSELECT, &LoadTextureDlg::OnCbnSelchangeObjselect)
END_MESSAGE_MAP()


// LoadTextureDlg message handlers

BOOL LoadTextureDlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();

	for (int i = 0; i < m_nNames; i++)
		m_objectCombo.AddString( m_objNames[i].c_str() );
	m_objectCombo.SetCurSel(0);

	return 0;
}

void LoadTextureDlg::OnBnClickedBrowse()
{
	TCHAR szFilters[] = _T ("Mipmapped PNG (*_a.png)|*_a.png||");
	CFileDialog dlg(TRUE, "png", "*_a.png", OFN_FILEMUSTEXIST | OFN_HIDEREADONLY ,szFilters);

	if (dlg.DoModal() == IDOK) {
		m_filePath = dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void LoadTextureDlg::OnCbnSelchangeObjselect()
{
	m_objSelected = m_objectCombo.GetCurSel();
}
