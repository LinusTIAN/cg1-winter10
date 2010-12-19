#pragma once
#include "afxwin.h"
#include "MyFogPrameters.h"


// CFogDialog dialog

class CFogDialog : public CDialog
{
	DECLARE_DYNAMIC(CFogDialog)

public:
	CFogDialog(MyFogPrameters &fogPrameters, CWnd* pParent = NULL);   // standard constructor
	virtual ~CFogDialog();

	
	BOOL OnInitDialog(); 

// Dialog Data
	enum { IDD = IDD_FogDialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


public:
	MyFogPrameters& getFogParams();

	DECLARE_MESSAGE_MAP()
public:
	CButton m_colorButton;
	afx_msg void OnBnClickedButton1();
	CEdit m_rColorCtrl;
	CEdit m_gColorCtrl;
	CEdit m_bColorCtrl;
	CString m_rColor;
	CString m_gColor;
	CString m_bColor;
	CComboBox m_modeCtrl;
	CString m_mode;
	CEdit m_densityCtrl;
	CString m_density;

private:
	MyFogPrameters m_fogPrameters;
public:
	CButton m_enabledCtrl;
	BOOL m_enabled;
};
