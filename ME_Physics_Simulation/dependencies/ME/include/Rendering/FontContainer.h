#pragma once

#include <vector>
#include <string>

namespace ME
{
	class ContainedFont final
	{
	public:

		ContainedFont();
		ContainedFont(unsigned int id, const char* filePath);

		unsigned int GetID();
		std::string GetFilePath();

	private:

		unsigned int m_ID;
		std::string m_FilePath;
	};

	class FontContainer final 
	{
	public:

		FontContainer();
		FontContainer(unsigned int reserve);

		ContainedFont* operator[](const unsigned int index);
		ContainedFont* GetWithID(const unsigned int id);

		ContainedFont* Add(const char* filePath);
		void Delete(const int index);

	private:

		std::vector<ContainedFont> m_Fonts;
		unsigned int m_NextFontID;

	};

}

