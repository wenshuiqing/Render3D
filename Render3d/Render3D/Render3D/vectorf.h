#pragma once
#include "mathf.h"
namespace mf
{
	struct Vector2
	{
	public:
		float x;

		float y;

	public:
		Vector2() :x(0), y(0)
		{
		}
		Vector2(float value) : x(value), y(value)
		{
		}

		Vector2(float values[]) : x(values[0]), y(values[1])
		{
		}

		Vector2(float x, float y) : x(x), y(y)
		{

		}

		static Vector2 One()
		{
			return Vector2(1.0f);
		}
		static Vector2 UnitX()
		{
			return Vector2(1.0f, 0);

		}
		static Vector2 UnitY()
		{
			return Vector2(0, 1.0f);
		}

		float Distance(Vector2 &value)const
		{
			Vector2 temp(x - value.x, y - value.y);

			return (float)sqrt(temp.x*temp.x + temp.y*temp.y);
		}
		float Dot(const Vector2 &value)const
		{
			return x * value.x + y * value.y;
		}


		float Magnitude()const
		{
			return (float)sqrt(x*x + y*y);
		}
		Vector2 Normalize()const
		{
			Vector2 temp(x, y);
			temp /= ((float)sqrt(temp.x*temp.x + temp.y*temp.y));
			return temp;
		}






		void Vector2::operator=(const Vector2 &value)
		{
			x = value.x;
			y = value.y;
		}
		Vector2 operator +()
		{
			return Vector2(x, y);
		}

		Vector2 operator +(const Vector2  &value)const
		{
			return Vector2(x + value.x, y + value.y);
		}


		Vector2 operator-()const
		{
			return  Vector2(-x, -y);
		}
		Vector2 operator-(const Vector2  &value)const
		{

			return  Vector2(x - value.x, y - value.y);
		}


		Vector2 operator *(const Vector2  &value)const
		{
			return  Vector2(value.x * x, value.y * y);
		}

		Vector2 operator *(float scale)const
		{
			return  Vector2(x * scale, y * scale);
		}
		void operator *=(float scale)
		{
			x *= scale;
			y *= scale;
		}
		Vector2 operator /(const Vector2  &value)const
		{
			return  Vector2(x / value.x, y / value.y);
		}
		Vector2 operator /(float scale)const
		{
			return  Vector2(x / scale, y / scale);
		}
		void operator /=(float scale)
		{
			x /= scale;
			y /= scale;
		}

		bool operator==(const Vector2  &value)const
		{
			return (x == value.x) && (y == value.y);
		}

		bool operator!=(const Vector2  &value)const
		{
			return (x != value.x) || (y != value.y);
		}

	};
	struct Vector3
	{
	public:
		float x;

		float y;

		float z;
	public:
		Vector3() :x(0), y(0), z(0)
		{
		}
		Vector3(float value) : x(value), y(value), z(value)
		{
		}

		Vector3(float values[]) : x(values[0]), y(values[1]), z(values[2])
		{
		}

		Vector3(float x, float y, float z) : x(x), y(y), z(z)
		{

		}

		static Vector3 One()
		{
			return Vector3(1.0f);
		}
		static Vector3 UnitX()
		{
			return Vector3(1.0f, 0, 0);
		}
		static Vector3 UnitY()
		{
			return Vector3(0, 1.0f, 0);
		}
		static Vector3 UnitZ()
		{
			return Vector3(0, 0, 1.0f);
		}
		static Vector3 Zero()
		{
			return Vector3(0.0f);
		}




		Vector3 Cross(const Vector3 &value)const
		{
			Vector3 result;
			result.x = y * value.z - y * value.z;
			result.y = z * value.x - z * value.x;
			result.z = x * value.y - x * value.y;
			return result;
		}


		float Distance(Vector3 &value)const
		{
			Vector3 temp(x - value.x, y - value.y, z - value.z);

			return (float)sqrt(temp.x*temp.x + temp.y*temp.y + temp.z + temp.z);
		}

		float Dot(const Vector3 &value)const
		{
			return x * value.x + y * value.y + z * value.z;
		}

		float Magnitude()const
		{
			return (float)sqrt(x*x + y*y + z*z);
		}
		void Normalized()
		{
			x /= (float)sqrt(x*x + y*y + z*z);
			y /= (float)sqrt(x*x + y*y + z*z);
			z /= (float)sqrt(x*x + y*y + z*z);
		}


		Vector3 Normalize()const
		{
			Vector3 temp(x, y, z);
			temp /= (float)sqrt(temp.x*temp.x + temp.y*temp.y + temp.z*temp.z);
			return temp;
		}
	





		void operator=(const Vector3 &value)
		{
			x = value.x;
			y = value.y;
			z = value.z;
		}
		Vector3 operator +()
		{
			return Vector3(x, y, z);
		}

		Vector3 operator +(const Vector3  &value)const
		{
			return Vector3(x + value.x, y + value.y, z + value.z);
		}
		void operator +=(const Vector3  &value)
		{
			x += value.x;
			y += value.y;
			z += value.z;
		}

		Vector3 operator-()const
		{
			return  Vector3(-x, -y, -z);
		}
		Vector3 operator-(const Vector3  &value)const
		{

			return  Vector3(x - value.x, y - value.y, z - value.z);
		}
		void operator-=(const Vector3  &value)
		{
			x -= value.x;
			y -= value.y;
			z -= value.z;
		}

		Vector3 operator *(const Vector3  &value)const
		{
			return  Vector3(value.x * x, value.y * y, value.z * z);
		}

		Vector3 operator *(float scale)const
		{
			return  Vector3(x * scale, y * scale, z * scale);
		}
		void operator *=(float scale)
		{
			x *= scale;
			y *= scale;
			z *= scale;
		}
		Vector3 operator /(const Vector3  &value)const
		{
			return  Vector3(x / value.x, y / value.y, z / value.z);
		}
		Vector3 operator /(float scale)const
		{
			return  Vector3(x / scale, y / scale, z / scale);
		}
		void operator /=(float scale)
		{
			x /= scale;
			y /= scale;
			z /= scale;
		}

		bool operator==(const Vector3  &value)const
		{
			return (x == value.x) && (y == value.y) && (z == value.z);
		}

		bool operator!=(const Vector3  &value)const
		{
			return (x != value.x) || (y != value.y) || (z != value.z);
		}

	};
	struct Vector4
	{
	public:
		float x;

		float y;

		float z;

		float w;
	public:
		Vector4() :x(0), y(0), z(0), w(0)
		{
		}
		Vector4(float value) : x(value), y(value), z(value), w(value)
		{
		}

		Vector4(float values[]) : x(values[0]), y(values[1]), z(values[2]), w(values[3])
		{
		}

		Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
		{

		}

		static Vector4 One()
		{
			return Vector4(1.0f);
		}
		static Vector4 UnitX()
		{
			return Vector4(1.0f, 0, 0, 0);
		}
		static Vector4 UnitY()
		{
			return Vector4(0, 1.0f, 0, 0);
		}
		static Vector4 UnitZ()
		{
			return Vector4(0, 0, 1.0f, 0);
		}
		static Vector4 UnitW()
		{
			return Vector4(0, 0, 0, 1.0f);
		}
		static Vector4 Zero()
		{
			return Vector4(0.0f);
		}

		float Distance(Vector4 &value)const
		{
			Vector3 temp(x - value.x, y - value.y, z - value.z);

			return (float)sqrt(temp.x*temp.x + temp.y*temp.y + temp.z + temp.z);
		}
		static float Distance(Vector4 value1, Vector4 value2)
		{
			Vector4 temp(value1 - value2);

			return (float)sqrt(temp.x*temp.x + temp.y*temp.y + temp.z + temp.z);
		}
		float Dot(const Vector4 &value)const
		{
			return x * value.x + y * value.y + z * value.z + w * value.w;
		}
		static float Dot(const Vector4 &left, const Vector4 &right)
		{
			return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
		}
		float Magnitude()const
		{
			return (float)sqrt(x*x + y*y + z*z + w*w);
		}
		static float Magnitude(const Vector4 &value)
		{
			return (float)sqrt(value.x*value.x + value.y*value.y + value.z * value.z + value.w * value.w);
		}

		Vector4 Normalize()const
		{
			Vector4 temp(x, y, z, w);

			return temp / Magnitude(temp);
		}
		static Vector4 Normalize(const Vector4 &value)
		{
			Vector4 temp(value.x, value.y, value.z, value.w);
			return temp / Magnitude(temp);
		}
		static Vector4 Lerp(const Vector4 & start, const Vector4 & end, float amount)
		{
			Vector4 result;
			result = start + (end - start)*amount;
			return result;
		}



		void Vector4::operator=(const Vector4 &value)
		{
			x = value.x;
			y = value.y;
			z = value.z;
		}
		Vector4 operator +()
		{
			return Vector4(x, y, z, w);
		}

		Vector4 operator +(const Vector4  &value)const
		{
			return Vector4(x + value.x, y + value.y, z + value.z, w + value.w);
		}

		Vector4 operator-()const
		{
			return  Vector4(-x, -y, -z, -w);
		}
		Vector4 operator-(const Vector4  &value)const
		{

			return  Vector4(x - value.x, y - value.y, z - value.z, w - value.w);
		}


		Vector4 operator *(const Vector4  &value)const
		{
			return  Vector4(value.x * x, value.y * y, value.z * z, value.w * w);
		}

		Vector4 operator *(float scale)const
		{
			return  Vector4(x * scale, y * scale, z * scale, w * scale);
		}

		Vector4 operator /(const Vector4  &value)const
		{
			return  Vector4(x / value.x, y / value.y, z / value.z, w / value.w);
		}
		Vector4 operator /(float scale)const
		{
			return  Vector4(x / scale, y / scale, z / scale, w / scale);
		}

		bool operator==(const Vector4  &value)const
		{
			return (x == value.x) && (y == value.y) && (z == value.z) && (w == value.w);
		}

		bool operator!=(const Vector4  &value)const
		{
			return (x != value.x) || (y != value.y) || (z != value.z) || (w != value.w);
		}

	};
}