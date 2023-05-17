#pragma once

namespace ME
{
	class Angle final
	{
	public:

		/* CONSTRUCTORS */
		Angle();
		Angle(float angle);

		/* OPERATORS */
		void operator=(const float angle);
		void operator+=(const float angle);
		Angle operator+(const float degrees);
		bool operator==(const Angle angle);
		
		/* GETTERS */
		float getDeg() const;
		float getRad() const;

	private:

		/* PRIVATE MEMBERS */
		float m_degrees;
	};
}


