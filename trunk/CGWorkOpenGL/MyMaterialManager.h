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
};
