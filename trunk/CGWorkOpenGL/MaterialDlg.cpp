// MaterialDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGL.h"
#include "MaterialDlg.h"


// CMaterialDlg dialog

IMPLEMENT_DYNAMIC(CMaterialDlg, CDialog)

CMaterialDlg::CMaterialDlg(MyMaterialManager& materialManager, CWnd* pParent /*=NULL*/)
	: CDialog(CMaterialDlg::IDD, pParent)
	, m_ambient(materialManager.m_ambient)
	, m_diffuse(materialManager.m_diffuse)
	, m_shininess(materialManager.m_shininess)
	, m_specular(materialManager.m_specular)
{
	m_materialManager = materialManager;
}

CMaterialDlg::~CMaterialDlg()
{
}

void CMaterialDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_MATERIAL_AMBIENT, m_ambient);
    DDV_MinMaxDouble(pDX, m_ambient, 0, 1);
    DDX_Text(pDX, IDC_MATERIAL_DIFFUSE, m_diffuse);
    DDV_MinMaxDouble(pDX, m_diffuse, 0, 1);
    DDX_Text(pDX, IDC_MATERIAL_SPECULAR, m_specular);
	DDV_MinMaxDouble(pDX, m_specular, 0, 1);

    DDX_Text(pDX, IDC_MATERIAL_SHININESS, m_shininess);
	DDV_MinMaxInt(pDX, m_shininess, 0, 128);
}

MyMaterialManager& CMaterialDlg::getMaterialManager(){
	m_materialManager.m_ambient = m_ambient;
	m_materialManager.m_diffuse = m_diffuse;
	m_materialManager.m_shininess = m_shininess;
	m_materialManager.m_specular = m_specular;

	return m_materialManager;
}

BEGIN_MESSAGE_MAP(CMaterialDlg, CDialog)
END_MESSAGE_MAP()


// CMaterialDlg message handlers
