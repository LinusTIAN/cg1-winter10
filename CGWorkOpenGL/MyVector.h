#pragma once

class MyVector
{
public:
	MyVector(void);
	MyVector(double x, double y, double z);	// build vector from origin
	MyVector(double from_x, double from_y, double from_z,
			 double to_x, double to_y, double to_z);	// build vector from point to point
	~MyVector(void);

	double m_x, m_y, m_z;

	double Size(void);
	MyVector operator/(double d);
	MyVector operator*(double d);
	MyVector& operator/=(double d);
	MyVector& operator*=(double d);
	MyVector cross(MyVector& rhs);
	operator bool() { return m_x || m_y || m_z; }
};
