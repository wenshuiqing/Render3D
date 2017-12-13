#pragma once
#include "mathf.h"
namespace mf
{
	
	struct Matrix4x4
	{
	public:
		float m11;
		float m12;
		float m13;
		float m14;
		float m21;
		float m22;
		float m23;
		float m24;
		float m31;
		float m32;
		float m33;
		float m34;
		float m41;
		float m42;
		float m43;
		float m44;
	public:
		Matrix4x4() :m11(0), m12(0), m13(0), m14(0), m21(0), m22(0), m23(0), m24(0),
			m31(0), m32(0), m33(0), m34(0), m41(0), m42(0), m43(0), m44(0)
		{

		}
		Matrix4x4(float value) :m11(value), m12(0), m13(0), m14(0), m21(0), m22(value), m23(0), m24(0),
			m31(0), m32(0), m33(value), m34(0), m41(0), m42(0), m43(0), m44(value)
		{

		}
		Matrix4x4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
			:m11(m11), m12(m12), m13(m13), m14(m14), m21(m21), m22(m22), m23(m23), m24(m24), m31(m31), m32(m32), m33(m33), m34(m34), m41(m41), m42(m42), m43(m43), m44(m44)
		{

		}


	public:
		Matrix4x4 operator +()const
		{
			return Matrix4x4(m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44);
		}

		Matrix4x4 operator +(const Matrix4x4 &value)const
		{
			Matrix4x4 result;
			result.m11 = m11 + value.m11;
			result.m12 = m12 + value.m12;
			result.m13 = m13 + value.m13;
			result.m14 = m14 + value.m14;
			result.m21 = m21 + value.m21;
			result.m22 = m22 + value.m22;
			result.m23 = m23 + value.m23;
			result.m24 = m24 + value.m24;
			result.m31 = m31 + value.m31;
			result.m32 = m32 + value.m32;
			result.m33 = m33 + value.m33;
			result.m34 = m34 + value.m34;
			result.m41 = m41 + value.m41;
			result.m42 = m42 + value.m42;
			result.m43 = m43 + value.m43;
			result.m44 = m44 + value.m44;
			return result;
		}

		Matrix4x4 operator -()const
		{
			return Matrix4x4(-m11, -m12, -m13, -m14, -m21, -m22, -m23, -m24, -m31, -m32, -m33, -m34, -m41, -m42, -m43, -m44);
		}

		Matrix4x4 operator -(const Matrix4x4 &value)const
		{
			Matrix4x4 result;
			result.m11 = m11 - value.m11;
			result.m12 = m12 - value.m12;
			result.m13 = m13 - value.m13;
			result.m14 = m14 - value.m14;
			result.m21 = m21 - value.m21;
			result.m22 = m22 - value.m22;
			result.m23 = m23 - value.m23;
			result.m24 = m24 - value.m24;
			result.m31 = m31 - value.m31;
			result.m32 = m32 - value.m32;
			result.m33 = m33 - value.m33;
			result.m34 = m34 - value.m34;
			result.m41 = m41 - value.m41;
			result.m42 = m42 - value.m42;
			result.m43 = m43 - value.m43;
			result.m44 = m44 - value.m44;
			return result;
		}

		Matrix4x4 operator *(const Matrix4x4 &value)const
		{
			Matrix4x4 result;
			result.m11 = m11 * value.m11 + m12 * value.m21 + m13 * value.m31 + m14 * value.m41;
			result.m12 = m11 * value.m12 + m12 * value.m22 + m13 * value.m32 + m14 * value.m42;
			result.m13 = m11 * value.m13 + m12 * value.m23 + m13 * value.m33 + m14 * value.m43;
			result.m14 = m11 * value.m14 + m12 * value.m24 + m13 * value.m34 + m14 * value.m44;
			result.m21 = m21 * value.m11 + m22 * value.m21 + m23 * value.m31 + m24 * value.m41;
			result.m22 = m21 * value.m12 + m22 * value.m22 + m23 * value.m32 + m24 * value.m42;
			result.m23 = m21 * value.m13 + m22 * value.m23 + m23 * value.m33 + m24 * value.m43;
			result.m24 = m21 * value.m14 + m22 * value.m24 + m23 * value.m34 + m24 * value.m44;
			result.m31 = m31 * value.m11 + m32 * value.m21 + m33 * value.m31 + m34 * value.m41;
			result.m32 = m31 * value.m12 + m32 * value.m22 + m33 * value.m32 + m34 * value.m42;
			result.m33 = m31 * value.m13 + m32 * value.m23 + m33 * value.m33 + m34 * value.m43;
			result.m34 = m31 * value.m14 + m32 * value.m24 + m33 * value.m34 + m34 * value.m44;
			result.m41 = m41 * value.m11 + m42 * value.m21 + m43 * value.m31 + m44 * value.m41;
			result.m42 = m41 * value.m12 + m42 * value.m22 + m43 * value.m32 + m44 * value.m42;
			result.m43 = m41 * value.m13 + m42 * value.m23 + m43 * value.m33 + m44 * value.m43;
			result.m44 = m41 * value.m14 + m42 * value.m24 + m43 * value.m34 + m44 * value.m44;
			return result;
		}

		Matrix4x4 operator *(float value)const
		{
			Matrix4x4 result;
			result.m11 = m11 * value;
			result.m12 = m11 * value;
			result.m13 = m11 * value;
			result.m14 = m11 * value;

			result.m21 = m21 * value;
			result.m22 = m21 * value;
			result.m23 = m21 * value;
			result.m24 = m21 * value;

			result.m31 = m31 * value;
			result.m32 = m31 * value;
			result.m33 = m31 * value;
			result.m34 = m31 * value;

			result.m41 = m41 * value;
			result.m42 = m41 * value;
			result.m43 = m41 * value;
			result.m44 = m41 * value;
			return result;
		}



		Matrix4x4 operator /(float value)const
		{
			Matrix4x4 result;
			result.m11 = m11 / value;
			result.m12 = m11 / value;
			result.m13 = m11 / value;
			result.m14 = m11 / value;
			result.m21 = m21 / value;
			result.m22 = m21 / value;
			result.m23 = m21 / value;
			result.m24 = m21 / value;
			result.m31 = m31 / value;
			result.m32 = m31 / value;
			result.m33 = m31 / value;
			result.m34 = m31 / value;
			result.m41 = m41 / value;
			result.m42 = m41 / value;
			result.m43 = m41 / value;
			result.m44 = m41 / value;
			return result;
		}

		bool operator ==(const Matrix4x4 &value)const
		{
			bool result =
				(m11 == value.m11) &&
				(m12 == value.m12) &&
				(m13 == value.m13) &&
				(m14 == value.m14) &&
				(m21 == value.m21) &&
				(m22 == value.m22) &&
				(m23 == value.m23) &&
				(m24 == value.m24) &&
				(m31 == value.m31) &&
				(m32 == value.m32) &&
				(m33 == value.m33) &&
				(m34 == value.m34) &&
				(m41 == value.m41) &&
				(m42 == value.m42) &&
				(m43 == value.m43) &&
				(m44 == value.m44);
			return result;
		}

		bool operator !=(const Matrix4x4 & value)
		{
			bool result =
				(m11 != value.m11) ||
				(m12 != value.m12) ||
				(m13 != value.m13) ||
				(m14 != value.m14) ||
				(m21 != value.m21) ||
				(m22 != value.m22) ||
				(m23 != value.m23) ||
				(m24 != value.m24) ||
				(m31 != value.m31) ||
				(m32 != value.m32) ||
				(m33 != value.m33) ||
				(m34 != value.m34) ||
				(m41 != value.m41) ||
				(m42 != value.m42) ||
				(m43 != value.m43) ||
				(m44 != value.m44);
			return result;
		}

	};
}