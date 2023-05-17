#include "RGBA.h"

namespace ME
{
	/* Sets to white by default */
	RGBA::RGBA() :m_Red(255), m_Green(255), m_Blue(255), m_Alpha(255) {}

	/* 
	* Sets RGBA colour parameters.
	* Makes sure RGBA values are between 0 and 255.
	*/
	RGBA::RGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : m_Red(r), m_Green(g), m_Blue(b), m_Alpha(a) {}

	/* Return RGBA colour parameters */
	unsigned char RGBA::GetR() const
	{
		return m_Red;
	}
	unsigned char RGBA::GetG() const
	{
		return m_Green;
	}
	unsigned char RGBA::GetB() const
	{
		return m_Blue;
	}
	unsigned char RGBA::GetA() const
	{
		return m_Alpha;
	}
}
