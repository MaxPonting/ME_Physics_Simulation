#pragma once

namespace ME
{
	/* Owns RGBA colour values. */
	class RGBA final
	{
	public:

		/* CONSTRUCTORS */
		RGBA();
		RGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

		/* GETTERS */
		unsigned char GetR() const;
		unsigned char GetG() const;
		unsigned char GetB() const;
		unsigned char GetA() const;

	private:

		/* MEMBERS */
		unsigned char m_Red, m_Green, m_Blue, m_Alpha;
	};
}


