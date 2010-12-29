#pragma once
#include "afxcmn.h"


// CMouseSensitivityDialog dialog

class CMouseSensitivityDialog : public CDialog
{
	DECLARE_DYNAMIC(CMouseSensitivityDialog)

public:
	CMouseSensitivityDialog(int sensivity,CWnd* pParent = NULL);   // standard constructor
	virtual ~CMouseSensitivityDialog();

	
	BOOL OnInitDialog(); 

// Dialog Data
	enum { IDD = IDD_MOUSE_SENSIVIITY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_sensitivityCtrl;
	int m_sensitivity;
};
