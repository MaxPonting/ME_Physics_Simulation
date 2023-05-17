#pragma once

namespace ME
{
	struct Vector2f;
	struct Vector2i final
	{
		/* CONSTRUCTORS */
		Vector2i();
		Vector2i(int x, int y);
		Vector2i(Vector2f vector2);

		//
		// Operators
		//
		void operator=(const Vector2i vector2);
		void operator+=(const Vector2i vector2);
		void operator-=(const Vector2i vector2);
		Vector2i operator+(const Vector2i vector2);
		Vector2i operator-(const Vector2i vector2);
		Vector2i operator*(const Vector2i vector2);
		Vector2i operator*(const float scale);
		Vector2i operator/(const Vector2i vector2);
		Vector2i operator/(const float scale);

		/* MEMBERS */
		int X, Y;

	};
}


