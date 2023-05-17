#include "Angle.h"
#include <cmath>

namespace ME
{

	Angle::Angle() :
		m_degrees(0) 
	{}

	Angle::Angle(float angle) : 
		m_degrees(std::fmodf(angle, 360)) 
	{}

	/* Set angle to between 0 and 360 */
	void Angle::operator=(float angle)
	{	
		m_degrees = std::fmodf(angle, 360);
	}

	void Angle::operator+=(const float angle)
	{
		m_degrees = std::fmodf(m_degrees + angle, 360);		
	}

	/* Set angle to between 0 and 360 */
	Angle Angle::operator+(float degrees)
	{
		return std::fmodf(m_degrees + degrees, 360);
	}

	bool Angle::operator==(Angle angle)
	{
		return m_degrees == angle.getDeg();
	}

	float Angle::getDeg() const
	{
		return m_degrees;
	}

	float Angle::getRad() const
	{
		return m_degrees * (3.14159265359 / 180);
	}
}