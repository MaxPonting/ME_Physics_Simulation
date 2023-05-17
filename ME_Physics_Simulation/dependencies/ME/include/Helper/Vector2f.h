#pragma once

#include "Vector2i.h"
#include <math.h>

namespace ME
{
	struct Vector2f final
	{
		/* CONSTRUCTORS */
		Vector2f();
		Vector2f(float x, float y);
		Vector2f(Vector2i vector2);

		//
		// Operators
		//
		void operator=(const Vector2f vector2);
		bool operator==(const Vector2f vector2);
		void operator+=(const Vector2f vector2);
		void operator-=(const Vector2f vector2);
		Vector2f operator+(const Vector2f vector2) const;		
		Vector2f operator-(const Vector2f vector2) const;
		Vector2f operator-() const;
		float operator*(const Vector2f vector2) const;
		Vector2f operator*(const float scale) const;
		Vector2f operator/(const Vector2f vector2) const;
		Vector2f operator/(const float scale) const;

		//
		// Helper Functions
		//
		float Magnitude();
		float LengthSqr();
		Vector2f virtual Normalize();
		Vector2f virtual Normalize(float magnitude);
		
		/* MEMBERS */
		float X, Y;
	};
}


