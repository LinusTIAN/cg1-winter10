// MaterialDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGL.h"
#include "MaterialDlg.h"


// CMaterialDlg dialog

IMPLEMENT_DYNAMIC(CMaterialDlg, CDialog)

CMaterialDlg::CMaterialDlg(MyMaterialManager& materialManager, CWnd* pParent /*=NULL*/)
	: CDialog(CMaterialDlg::IDD, pParent)
	, m_sWrap(_T(""))
	, m_tWrap(_T(""))
	, m_sAuto(materialManager.m_sAuto)
	, m_tAuto(materialManager.m_tAuto)
	, m_sType(_T(""))
	, m_tType(_T(""))
{
	m_materialManager = materialManager;
	
	if ( materialManager.m_sRepeat)
		m_sWrap = "GL_REPEAT";
	else
		m_sWrap = "GL_CLAMP";
	
	if ( materialManager.m_tRepeat)
		m_tWrap = "GL_REPEAT";
	else
		m_tWrap = "GL_CLAMP";

	
	switch(materialManager.m_sType){
	case  1:
		m_sType = "Eye Linear";
		break;
	case 2:
		m_sType = "Object Linear";
		break;
	default:
		m_sType = "Sphere Map";
		break;
	}

	
	switch(materialManager.m_tType){
	case  1:
		m_tType = "Eye Linear";
		break;
	case 2:
		m_tType = "Object Linear";
		break;
	default:
		m_tType = "Sphere Map";
		break;
	}
}

CMaterialDlg::~CMaterialDlg()
{
}

void CMaterialDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MATERIAL_AMBIENT, m_materialManager.m_ambient);
	DDV_MinMaxDouble(pDX, m_materialManager.m_ambient, 0, 1);
	DDX_Text(pDX, IDC_MATERIAL_DIFFUSE,m_materialManager. m_diffuse);
	DDV_MinMaxDouble(pDX, m_materialManager.m_diffuse, 0, 1);
	DDX_Text(pDX, IDC_MATERIAL_SPECULAR, m_materialManager.m_specular);
	DDV_MinMaxDouble(pDX, m_materialManager.m_specular, 0, 1);

	DDX_Text(pDX, IDC_MATERIAL_SHININESS, m_materialManager.m_shininess);
	DDV_MinMaxInt(pDX, m_materialManager.m_shininess, 0, 128);

	DDX_CBString(pDX, IDC_COMBO1, m_sWrap);
	DDX_CBString(pDX, IDC_COMBO2, m_tWrap);
	DDX_Check(pDX, IDC_CHECK1, m_sAuto);
	DDX_Check(pDX, IDC_CHECK2, m_tAuto);
	DDX_CBString(pDX, IDC_COMBO3, m_sType);
	DDX_CBString(pDX, IDC_COMBO4, m_tType);

	DDX_Text(pDX, IDC_EDIT2, m_materialManager.m_sCoord1);
	DDX_Text(pDX, IDC_EDIT3, m_materialManager.m_sCoord2);
	DDX_Text(pDX, IDC_EDIT4, m_materialManager.m_sCoord3);
	DDX_Text(pDX, IDC_EDIT5, m_materialManager.m_sCoord4);
	DDX_Text(pDX, IDC_EDIT6, m_materialManager.m_tCoord1);
	DDX_Text(pDX, IDC_EDIT7, m_materialManager.m_tCoord2);
	DDX_Text(pDX, IDC_EDIT8, m_materialManager.m_tCoord3);
	DDX_Text(pDX, IDC_EDIT9, m_materialManager.m_tCoord4);
}

MyMaterialManager& CMaterialDlg::getMaterialManager(){

	m_materialManager.m_sRepeat = (m_sWrap == "GL_REPEAT"  || m_sWrap =="");
	m_materialManager.m_tRepeat = (m_tWrap == "GL_REPEAT"  || m_tWrap =="");

	m_materialManager.m_sAuto = m_sAuto;
	m_materialManager.m_tAuto = m_tAuto;
						
	if (m_sType == "Eye Linear")
		m_materialManager.m_sType = 1;
	else if (m_sType == "Object Linear")
		m_materialManager.m_sType = 2;
	else
		m_materialManager.m_sType = 3;


	if (m_tType == "Eye Linear")
		m_materialManager.m_tType = 1;
	else if (m_tType == "Object Linear")
		m_materialManager.m_tType = 2;
	else
		m_materialManager.m_tType = 3;

	return m_materialManager;
}

BOOL CMaterialDlg::OnInitDialog(){
    CDialog::OnInitDialog();

	return TRUE;

}


BEGIN_MESSAGE_MAP(CMaterialDlg, CDialog)
	ON_EN_CHANGE(IDC_EDIT2, &CMaterialDlg::OnEnChangeEdit2)
END_MESSAGE_MAP()


// CMaterialDlg message handlers

void CMaterialDlg::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
