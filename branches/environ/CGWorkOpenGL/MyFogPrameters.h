#pragma once

typedef enum 
{
	FOG_GL_EXP,
	FOG_GL_EXP2,
	FOG_GL_LINEAR
} FogType;

class MyFogPrameters
{
public:
	MyFogPrameters(void);
	~MyFogPrameters(void);

	void setupFog();

public:
	bool enabled;

	int m_r;
	int m_g;
	int m_b;

	double m_density;
	FogType m_type;

};
