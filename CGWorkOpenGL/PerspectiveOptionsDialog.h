#pragma once
#include "afxwin.h"


// CPerspectiveOptionsDialog dialog

class CPerspectiveOptionsDialog : public CDialog
{
	DECLARE_DYNAMIC(CPerspectiveOptionsDialog)

public:
	CPerspectiveOptionsDialog(double dVal, CWnd* pParent = NULL);   // standard constructor
	virtual ~CPerspectiveOptionsDialog();

// Dialog Data
	enum { IDD = IDD_PERSPECTIVE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_dCtl;
	CString m_dVal;
};
