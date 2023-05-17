#include "Vector2i.h"
#include "Vector2f.h"

namespace ME
{
	Vector2i::Vector2i() :
		X(0),
		Y(0)
	{}

	Vector2i::Vector2i(int x, int y) :
		X(x),
		Y(y)
	{}

	Vector2i::Vector2i(Vector2f vector2) :
		X(vector2.X),
		Y(vector2.Y)
	{}

	void Vector2i::operator=(const Vector2i vector2)
	{
		X = vector2.X; Y = vector2.Y;
	}

	void Vector2i::operator+=(const Vector2i vector2)
	{
		X += vector2.X; Y += vector2.Y;
	}

	void Vector2i::operator-=(const Vector2i vector2)
	{
		X -= vector2.X; Y -= vector2.Y;
	}

	Vector2i Vector2i::operator+(const Vector2i vector2)
	{
		return Vector2i(X + vector2.X, Y + vector2.Y);
	}

	Vector2i Vector2i::operator-(const Vector2i vector2)
	{
		return Vector2i(X - vector2.X, Y - vector2.Y);
	}

	Vector2i Vector2i::operator*(const Vector2i vector2)
	{
		return Vector2i(X * vector2.X, Y * vector2.Y);
	}

	Vector2i Vector2i::operator*(const float scale)
	{
		return Vector2i(X * scale, Y * scale);
	}

	Vector2i Vector2i::operator/(const Vector2i vector2)
	{
		return Vector2i(X / vector2.X, Y / vector2.Y);
	}

	Vector2i Vector2i::operator/(const float scale)
	{
		return Vector2i(X / scale, Y / scale);
	}

	
}
