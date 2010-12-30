#pragma once

#include <string>
#include "afxwin.h"

using std::string;

// LoadTextureDlg dialog

class LoadTextureDlg : public CDialog
{
	DECLARE_DYNAMIC(LoadTextureDlg)

public:
	LoadTextureDlg(string *objNames, int len, CWnd* pParent = NULL);   // standard constructor
	virtual ~LoadTextureDlg();
	BOOL OnInitDialog(void);

// Dialog Data
	enum { IDD = IDD_TEXTUREDIALOG };

	CString m_filePath;
	CComboBox m_objectCombo;
	int m_objSelected;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	string *m_objNames;
	int m_nNames;
public:
	afx_msg void OnBnClickedBrowse();
	afx_msg void OnCbnSelchangeObjselect();
};
