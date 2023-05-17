#include "Vector2f.h"

namespace ME
{
	Vector2f::Vector2f() :
		X(0),
		Y(0)
	{}

	Vector2f::Vector2f(float x, float y) :
		X(x),
		Y(y)
	{}

	Vector2f::Vector2f(Vector2i vector2) :
		X(vector2.X),
		Y(vector2.Y)
	{}

	void Vector2f::operator=(const Vector2f vector2)
	{
		X = vector2.X; Y = vector2.Y;
	}

	bool Vector2f::operator==(const Vector2f vector2)
	{
		return X == vector2.X && Y == vector2.Y;
	}

	void Vector2f::operator+=(const Vector2f vector2)
	{
		X += vector2.X; Y += vector2.Y;
	}

	void Vector2f::operator-=(const Vector2f vector2)
	{
		X -= vector2.X; Y -= vector2.Y;
	}

	Vector2f Vector2f::operator+(const Vector2f vector2) const
	{
		return Vector2f(X + vector2.X, Y + vector2.Y);
	}

	Vector2f Vector2f::operator-(const Vector2f vector2) const
	{
		return Vector2f(X - vector2.X, Y - vector2.Y);
	}

	Vector2f Vector2f::operator-() const
	{
		return Vector2f(-X, -Y);
	}

	float Vector2f::operator*(const Vector2f vector2) const
	{
		return X * vector2.X + Y * vector2.Y;
	}

	Vector2f Vector2f::operator*(const float scale) const
	{
		return Vector2f(X * scale, Y * scale);
	}

	Vector2f Vector2f::operator/(const Vector2f vector2) const
	{
		return Vector2f(X / vector2.X, Y / vector2.Y);
	}

	Vector2f Vector2f::operator/(const float scale) const
	{
		return Vector2f(X / scale, Y / scale);
	}

	float Vector2f::Magnitude()
	{
		return pow(LengthSqr(), 0.5);
	}

	float Vector2f::LengthSqr()
	{
		return X * X + Y * Y;
	}

	Vector2f Vector2f::Normalize()
	{
		float magnitude = Magnitude();
		if (magnitude == 0) return Vector2f(0, 0);
		return Vector2f(X * 1 / magnitude, Y * 1 / magnitude);
	}

	Vector2f Vector2f::Normalize(float magnitude)
	{
		if (magnitude == 0) return Vector2f(0, 0);
		return Vector2f(X * 1 / magnitude, Y * 1 / magnitude);
	}

}