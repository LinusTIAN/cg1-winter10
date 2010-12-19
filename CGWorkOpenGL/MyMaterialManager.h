#pragma once

class MyMaterialManager
{
public:
	MyMaterialManager(void);
	~MyMaterialManager(void);

	void setupMaterialInScene();

public:
	
    // ambient property of the material
    double m_ambient;
    // Diffuse property of the material
    double m_diffuse;
    // shininess property of the material
    int m_shininess;
    // specular property of the material (integer values only)
    double m_specular;

	bool m_sRepeat;
	bool m_tRepeat;
		
	bool m_sAuto;
	bool m_tAuto;
	int m_sType;
	int m_tType;
	double m_sCoord1;
	double m_sCoord2;
	double m_sCoord3;
	double m_sCoord4;
	double m_tCoord1;
	double m_tCoord2;
	double m_tCoord3;
	double m_tCoord4;


};
