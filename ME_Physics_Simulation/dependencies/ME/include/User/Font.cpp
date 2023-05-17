#include "Font.h"

namespace ME
{
	Font::Font() :
		m_FontID(0)
	{}

	Font::Font(unsigned int id) :
		m_FontID(id)
	{}

	unsigned int Font::GetFontID()
	{
		return m_FontID;
	}
}
