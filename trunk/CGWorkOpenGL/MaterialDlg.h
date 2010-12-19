#pragma once

#include "MyMaterialManager.h"
#include "afxwin.h"
// CMaterialDlg dialog

class CMaterialDlg : public CDialog
{
	DECLARE_DYNAMIC(CMaterialDlg)

public:
	CMaterialDlg(MyMaterialManager& materialManager, CWnd* pParent = NULL);   // standard constructor
	virtual ~CMaterialDlg();

	MyMaterialManager& getMaterialManager();

// Dialog Data
	enum { IDD = IDD_MATERIAL_DLG };

	BOOL OnInitDialog();


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	MyMaterialManager m_materialManager;
	CString m_sWrap;
	CString m_tWrap;
	BOOL m_sAuto;
	BOOL m_tAuto;
	CString m_sType;
	CString m_tType;
};
