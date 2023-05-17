#pragma once

#include <string>

#include "ComponentRef.h"
#include "../User/Font.h"
#include "../Helper/RGBA.h"

namespace ME
{
	class TextRenderer final : public ComponentRef
	{
	public:

		TextRenderer();
		TextRenderer(unsigned int id, ECS* ecs);

		void SetText(std::string text);
		void SetFont(Font font);
		void SetFontSize(unsigned int size);
		void SetColour(RGBA colour);
		void SetLayer(int layer);

		std::string GetText();
		Font GetFont();
		unsigned int GetTextSize();
		RGBA GetColour();
		int GetLayer();

	};
}


