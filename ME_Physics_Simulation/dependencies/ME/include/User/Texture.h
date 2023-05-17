#pragma once

namespace ME
{
	class Texture final
	{
	public:

		/* CONSTRUCTORS */
		Texture();
		Texture(unsigned int id);

		/* GETTERS */
		unsigned int GetTextureID() const;

	private:

		unsigned int m_TextureID;

	};
}


