#pragma once
#include "vectorf.h"
#include "matrix.h"
#include "color.h"
#include "texture.h"
namespace mf
{
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//vector2
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	float Distance(Vector2 value1, Vector2 value2)
	{
		Vector2 temp(value1 - value2);

		return (float)sqrt(temp.x*temp.x + temp.y*temp.y);
	}
	float Dot(const Vector2 &left, const Vector2 &right)
	{
		return left.x * right.x + left.y * right.y;
	}
	float Magnitude(const Vector2 &value)
	{
		return (float)sqrt(value.x*value.x + value.y*value.y);
	}
	Vector2 Lerp(const Vector2 & start, const Vector2 & end, float amount)
	{
		Vector2 result;
		result = start + (end - start)*clamp(amount);
		return result;
	}
	Vector2 Normalize(const Vector2 &value)
	{
		Vector2 temp(value.x, value.y);
		temp /= ((float)sqrt(temp.x*temp.x + temp.y*temp.y));
		return temp;
	}

	Vector2 Reflect(Vector2 vector, Vector2 normal)
	{
		Vector2 result = (normal - vector);
		result /= ((float)sqrt(result.x*result.x + result.y*result.y));
		return result;
	}

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//vector3
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	Vector3 Cross(const Vector3 &left, const Vector3 &right)
	{
		Vector3 result;
		result.x = left.y * right.z - right.y * left.z;
		result.y = left.z * right.x - right.z * left.x;
		result.z = left.x * right.y - right.x * left.y;
		return result;
	}
	float Distance(Vector3 value1, Vector3 value2)
	{
		Vector3 temp(value1 - value2);

		return (float)sqrt(temp.x*temp.x + temp.y*temp.y + temp.z + temp.z);
	}
	float Dot(const Vector3 &left, const Vector3 &right)
	{
		return left.x * right.x + left.y * right.y + left.z * right.z;
	}
	float Magnitude(const Vector3 &value)
	{
		return (float)sqrt(value.x*value.x + value.y*value.y + value.z * value.z);
	}
	Vector3 Normalize(const Vector3 &value)
	{
		Vector3 temp(value.x, value.y, value.z);
		temp /= (float)sqrt(temp.x*temp.x + temp.y*temp.y + temp.z * temp.z);
		return temp;
	}
	Vector3 Lerp(const Vector3 & start, const Vector3 & end, float amount)
	{
		Vector3 result;
		result = start + (end - start)*clamp(amount);
		return result;
	}
	Vector3 Reflect(Vector3 vector, Vector3 normal)
	{
		Vector3 result = (normal - vector);
		result /= (float)sqrt(result.x*result.x + result.y*result.y + result.z * result.z);
		return result;
	}
	Vector3 TransformCoordinate(Vector3 &coord, Matrix4x4 &transMat)
	{
		Vector3 result(0.0f);
		result.x = coord.x * transMat.m11 + coord.y * transMat.m21 + coord.z * transMat.m31 + 1.0f * transMat.m41;
		result.y = coord.x * transMat.m12 + coord.y * transMat.m22 + coord.z * transMat.m32 + 1.0f * transMat.m42;
		result.z = coord.x * transMat.m13 + coord.y * transMat.m23 + coord.z * transMat.m33 + 1.0f * transMat.m43;
		float w = coord.x * transMat.m14 + coord.y * transMat.m24 + coord.z * transMat.m34 + 1.0f * transMat.m44;
		result /= w;
		return result;
	}



	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//Matrix4x4
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	Matrix4x4 LookAtRH(Vector3 &cameraPos, Vector3 &target, Vector3 &up)
	{
		Vector3 Zaxis = cameraPos - target;
		Zaxis = mf::Normalize(Zaxis);

		Vector3 Xaxis = mf::Normalize(mf::Cross(up, Zaxis));

		Vector3 Yaxis = mf::Normalize(mf::Cross(Zaxis, Xaxis));

		Matrix4x4 result;

		result.m11 = Xaxis.x;
		result.m12 = Xaxis.y;
		result.m13 = Xaxis.z;
		result.m14 = 0.0f;
		result.m21 = Yaxis.x;
		result.m22 = Yaxis.y;
		result.m23 = Yaxis.z;
		result.m24 = 0.0f;
		result.m31 = Zaxis.x;
		result.m32 = Zaxis.y;
		result.m33 = Zaxis.z;
		result.m34 = 0.0f;
		result.m41 = -mf::Dot(Xaxis, cameraPos);
		result.m42 = -mf::Dot(Yaxis, cameraPos);
		result.m43 = -mf::Dot(Zaxis, cameraPos);
		result.m44 = 1.0f;


		return result;

	}

	Matrix4x4 LookAtLH(Vector3 &cameraPos, Vector3 &target, Vector3 &up)
	{
		Vector3 Zaxis = target - cameraPos;
		Zaxis = mf::Normalize(Zaxis);

		Vector3 Xaxis = mf::Normalize(mf::Cross(up, Zaxis));

		Vector3 Yaxis = mf::Normalize(mf::Cross(Zaxis, Xaxis));

		Matrix4x4 result;

		result.m11 = Xaxis.x;
		result.m12 = Xaxis.y;
		result.m13 = Xaxis.z;
		result.m14 = 0.0f;
		result.m21 = Yaxis.x;
		result.m22 = Yaxis.y;
		result.m23 = Yaxis.z;
		result.m24 = 0.0f;
		result.m31 = Zaxis.x;
		result.m32 = Zaxis.y;
		result.m33 = Zaxis.z;
		result.m34 = 0.0f;
		result.m41 = -mf::Dot(Xaxis, cameraPos);
		result.m42 = -mf::Dot(Yaxis, cameraPos);
		result.m43 = -mf::Dot(Zaxis, cameraPos);
		result.m44 = 1.0f;


		return result;

	}
	Matrix4x4 Translation(Vector3 &value)
	{
		Matrix4x4 result(1.0f);
		result.m41 = value.x;
		result.m42 = value.y;
		result.m43 = value.z;

		return result;
	}


	Matrix4x4 PerspectiveFovRH(float fov, float aspect, float znear, float zfar)
	{
		Matrix4x4 result(1.0f);

		result.m11 = 1.0f / (float)(tan(fov * 0.5f) * aspect);
		result.m22 = 1.0f / (float)tan(fov * 0.5f);
		result.m33 = zfar / (znear - zfar);
		result.m44 = 0.0f;
		result.m34 = -1.0f;
		result.m43 = (-znear * zfar) / (zfar - znear);

		return result;
	}

	Matrix4x4 PerspectiveFovLH(float fov, float aspect, float znear, float zfar)
	{
		Matrix4x4 result(1.0f);

		result.m11 = 1.0f / (float)(tan(fov * 0.5f) * aspect);
		result.m22 = 1.0f / (float)tan(fov * 0.5f);
		result.m33 = zfar / (zfar - znear);
		result.m44 = 0.0f;
		result.m34 = 1.0f;
		result.m43 = (znear * zfar) / (znear - zfar);

		return result;
	}

	Matrix4x4 RotationX(float angle)
	{
		Matrix4x4 result(
			1, 0, 0, 0,
			0, (float)cos(angle), (float)sin(angle), 0,
			0, -(float)sin(angle), (float)cos(angle), 0,
			0, 0, 0, 1.0f
		);
		return result;
	}
	Matrix4x4 RotationY(float angle)
	{
		Matrix4x4 result(
			(float)cos(angle), 0.0f, -(float)sin(angle), 0,
			0.0f, 1.0f, 0.0f, 0,
			(float)sin(angle), 0, (float)cos(angle), 0,
			0, 0, 0, 1.0f
		);
		return result;
	}
	Matrix4x4 RotationZ(float angle)
	{
		Matrix4x4 result(
			(float)cos(angle), (float)sin(angle), 0, 0,
			-(float)sin(angle), (float)cos(angle), 0, 0,
			0, 0, 1.0f, 0,
			0, 0, 0, 1.0f
		);
		return result;
	}
	Matrix4x4 RotationYawPitchRoll(float yaw, float pitch, float roll)
	{
		Matrix4x4 result;
		result = RotationY(yaw)* RotationX(pitch)* RotationZ(roll);
		return result;
	}
	Matrix4x4 Rotate(Vector3 &rotate)
	{
		Matrix4x4 result;
		result = RotationY(rotate.y)* RotationX(rotate.x)* RotationZ(rotate.z);
		return result;
	}

	Matrix4x4 Scale(float x, float y, float z)
	{
		Matrix4x4 result(1.0f);
		result.m11 *= x;
		result.m22 *= y;
		result.m33 *= z;

		return result;
	}
	Matrix4x4 Scale(Vector3 &scale)
	{
		return Scale(scale.x, scale.y, scale.z);
	}

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//color
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	Color Lerp(const Color & start, const Color & end, float amount)
	{
		Color result;
		result = start + (end - start)*clamp(amount);
		return result;
	}
	mf::Color tex2D(Texture *tex, Vector2 uv)
	{
		if (tex->buffer == nullptr)
		{
			return mf::Color(1.0f);
		}
		int u = abs((int)(uv.x*tex->width) % tex->width);
		int v = abs((int)(uv.y*tex->height) % tex->height);

		int pos = (u + v * tex->width) * 4;
		byte b = tex->buffer[pos];
		byte g = tex->buffer[pos + 1];
		byte r = tex->buffer[pos + 2];
		byte a = tex->buffer[pos + 3];

		return  mf::Color(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
	}

	mf::Color tex2D(Texture *tex, float tu, float tv)
	{
		if (tex->buffer == nullptr)
		{
			return mf::Color(1.0f);
		}
		int u = abs((int)(tu*tex->width) % tex->width);
		int v = abs((int)(tv*tex->height) % tex->height);

		int pos = (u + v * tex->width) * 4;
		byte b = tex->buffer[pos];
		byte g = tex->buffer[pos + 1];
		byte r = tex->buffer[pos + 2];
		byte a = tex->buffer[pos + 3];

		return  mf::Color(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
	}

	////////////////////////////////////////////////////

	static Vector3 operator*(const Vector3 &left, const Matrix4x4 &right)
	{
		Vector3 result(0.0f);
		result.x = left.x * right.m11 + left.y * right.m21 + left.z * right.m31 + 1.0f * right.m41;
		result.y = left.x * right.m12 + left.y * right.m22 + left.z * right.m32 + 1.0f * right.m42;
		result.z = left.x * right.m13 + left.y * right.m23 + left.z * right.m33 + 1.0f * right.m43;
		float w = left.x * right.m14 + left.y * right.m24 + left.z * right.m34 + 1.0f * right.m44;
		result /= w;
		return result;
	}


	static Color operator*(const Vector3 &value, const Color &value1)
	{
		return Color(value.x*value1.r, value.y*value1.g, value.z*value1.b, 1.0f);
	}

}