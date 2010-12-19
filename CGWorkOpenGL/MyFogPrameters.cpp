#include "MyFogPrameters.h"

MyFogPrameters::MyFogPrameters(void)
{
	m_r = m_g = m_b = 255;
	m_density = 0.35;
	m_type = FOG_GL_EXP;

	enabled = false;
}

MyFogPrameters::~MyFogPrameters(void)
{
}
