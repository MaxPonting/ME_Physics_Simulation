#include "FontContainer.h"

namespace ME
{
	ContainedFont::ContainedFont() :
		m_ID(0),
		m_FilePath(std::string())
	{}

	ContainedFont::ContainedFont(unsigned int id, const char* filePath) :
		m_ID(id),
		m_FilePath(filePath)
	{}

	unsigned int ContainedFont::GetID()
	{
		return m_ID;
	}

	std::string ContainedFont::GetFilePath()
	{
		return m_FilePath;
	}

	FontContainer::FontContainer() :
		m_NextFontID(0)
	{}

	FontContainer::FontContainer(unsigned int reserve) :
		m_NextFontID(0)
	{
		m_Fonts.reserve(reserve);
	}

	ContainedFont* FontContainer::operator[](const unsigned int index)
	{
		if (index >= m_Fonts.size()) return nullptr;

		return &m_Fonts[index];
	}

	ContainedFont* FontContainer::GetWithID(const unsigned int id)
	{
		for (int i = 0; i < m_Fonts.size(); i++)
		{
			if (m_Fonts[i].GetID() == id) return &m_Fonts[i];
		}

		return nullptr;
	}

	ContainedFont* FontContainer::Add(const char* filePath)
	{
		m_Fonts.emplace_back(ContainedFont(++m_NextFontID, filePath));
		return &m_Fonts[m_Fonts.size() - 1];
	}

	void FontContainer::Delete(const int index)
	{
	}
}
