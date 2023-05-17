#pragma once

namespace ME
{
	class Font final
	{
	public:

		Font();
		Font(unsigned int id);

		unsigned int GetFontID();

	private:

		unsigned int m_FontID;
	};
}


