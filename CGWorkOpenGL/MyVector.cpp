#include "MyVector.h"
#include <cmath>

MyVector::MyVector(void)
{
	m_x = m_y = m_z = 0;
}

MyVector::MyVector(double x, double y, double z)
{
	m_x = x; m_y = y; m_z = z;
}

MyVector::MyVector(double from_x, double from_y, double from_z,
				   double to_x, double to_y, double to_z)
{
	m_x = to_x - from_x;
	m_y = to_y - from_y;
	m_z = to_z - from_z;
}

MyVector::~MyVector(void)
{
}

double MyVector::Size(void)
{
	return std::sqrt(m_x*m_x + m_y*m_y + m_z*m_z);
}

MyVector MyVector::operator/(double d)
{
	return MyVector(m_x/d, m_y/d, m_z/d);
}

MyVector MyVector::operator*(double d)
{
	return MyVector(m_x*d, m_y*d, m_z*d);
}

MyVector& MyVector::operator/=(double d)
{
	 m_x /= d; m_y /= d; m_z /= d;
	 return *this;
}

MyVector& MyVector::operator*=(double d)
{
	 m_x *= d; m_y *= d; m_z *= d;
	 return *this;
}
MyVector MyVector::cross(MyVector& rhs)
{
	return MyVector(	m_y*rhs.m_z - m_z*rhs.m_y,
						m_z*rhs.m_x - m_x*rhs.m_z,
						m_x*rhs.m_y - m_y*rhs.m_x	);
}
