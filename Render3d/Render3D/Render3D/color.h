#pragma once
#include "mathf.h"
namespace mf
{
	struct Color
	{
	public:
		float r;
		float g;
		float b;
		float a;


		Color()
		{
			r = g = b = a = 0.0f;
		}

		Color(float r1, float g1, float b1, float a1)
		{
			r = clamp(r1);
			g = clamp(g1);
			b = clamp(b1);
			a = clamp(a1);
		}
		Color(float value)
		{
			r = g = b = a = clamp(value);
		}



	public:
		Color operator +()
		{
			return Color(r, g, b, a);
		}

		Color operator +(const Color  &value)const
		{
			return Color(r + value.r, g + value.g, b + value.b, a + value.a);
		}
		void operator+=(const Color  &value)
		{

			r = clamp(r + value.r);
			g = clamp(g + value.g);
			b = clamp(b + value.b);
			a = clamp(a + value.a);
		}
		Color operator-()const
		{
			return  Color(-r, -g, -b, -a);
		}
		Color operator-(const Color  &value)const
		{

			return  Color(r - value.r, g - value.g, b - value.b, a - value.a);
		}
		void operator-=(const Color  &value)
		{

			r = clamp(r - value.r);
			g = clamp(g - value.g);
			b = clamp(b - value.b);
			a = clamp(a - value.a);
		}

		Color operator *(const Color  &value)const
		{
			return  Color(value.r * r, value.g * g, value.b * b, value.a * a);
		}

		Color operator *(float scale)const
		{
			return  Color(r * scale, g * scale, b * scale, a * scale);
		}
		void operator*=(const Color  &value)
		{
			r = clamp(r * value.r);
			g = clamp(g * value.g);
			b = clamp(b * value.b);
			a = clamp(a * value.a);
		}
		Color operator /(const Color  &value)const
		{
			return  Color(r / value.r, g / value.g, b / value.b, a / value.a);
		}
		Color operator /(float scale)const
		{
			return  Color(r / scale, g / scale, b / scale, a / scale);
		}

		void operator/=(const Color  &value)
		{
			r = clamp(r / value.r);
			g = clamp(g / value.g);
			b = clamp(b / value.b);
			a = clamp(a / value.a);
		}

		bool operator==(const Color  &value)const
		{
			return (r == value.r) && (g == value.g) && (b == value.b) && (a == value.a);
		}

		bool operator!=(const Color  &value)const
		{
			return (r != value.r) || (g != value.g) || (b != value.b) || (a != value.a);
		}
	};
}