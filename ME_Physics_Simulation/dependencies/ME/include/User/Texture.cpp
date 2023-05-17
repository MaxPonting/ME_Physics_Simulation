#include "Texture.h"

namespace ME
{
	Texture::Texture() :
		m_TextureID(0)
	{}


	Texture::Texture(unsigned int id) :
		m_TextureID(id)
	{}

	
	unsigned int Texture::GetTextureID() const
	{
		return m_TextureID;
	}
}
