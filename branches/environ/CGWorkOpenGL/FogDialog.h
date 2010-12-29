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
	CString m_mode;

private:
	MyFogPrameters m_fogPrameters;
public:
	BOOL m_enabled;
};
