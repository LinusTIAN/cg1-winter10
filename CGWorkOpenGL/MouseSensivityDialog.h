#pragma once


// CMouseSensivityDialog dialog

class CMouseSensivityDialog : public CDialog
{
	DECLARE_DYNAMIC(CMouseSensivityDialog)

public:
	CMouseSensivityDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMouseSensivityDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
