#pragma once
#include <math.h>
namespace mf
{
	#define PI 3.141592653
	int equal(double elem1, double elem2)
	{
		if ((elem1 - elem2 < 0.0000001) && (elem1 - elem2 > -0.0000001))
			return 1;	//相等
		else
			return 0;	//不相等
	}

	double power_unsigned_exp(double base, unsigned int exponent)
	{
		double result = 0.0;

		if (0 == exponent)
			return 1.0;
		if (1 == exponent)
			return base;

		result = power_unsigned_exp(base, exponent / 2);
		if (exponent & 1 == 1)
			result *= base;

		return result;
	}

	double pow(double base, int exponent)
	{
		unsigned int abs_exponent = exponent;
		double result = 0.0;
		double invalid_input = 0;

		if (equal(base, 0.0) && exponent < 0)
		{
			invalid_input = 1;
			return 0.0;
		}

		if (exponent < 0)
			abs_exponent = (unsigned int)(-exponent);

		result = power_unsigned_exp(base, abs_exponent >> 1);
		result *= result;

		if (result < 0)
			result = 1.0 / result;

		return result;
	}


	float radians(float value)
	{
		return value / 180.f*PI;
	}
	float clamp(float value, float min1 = 0, float max1 = 1)
	{
		return max(min1, min(value, max1));
	}
	float lerp(float min, float max, float gradient)
	{
		return min + (max - min) * clamp(gradient);
	}
	float smoothStep(float min,float max,float x)
	{
		if (x<min)
		{
			return 0.0f;
		}
		if (x>max)
		{
			return 1.0f;
		}
		float temp = -2 * ((x - min) / (max - min))*((x - min) / (max - min))*((x - min) / (max - min))
			+ 3 * ((x - min) / (max - min))*((x - min) / (max - min));

		return temp;
	}
}