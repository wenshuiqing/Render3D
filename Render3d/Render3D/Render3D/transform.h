#pragma once
#include "rmathf.h"

enum class Space
{
	Self,
	World
};
enum class Axis
{
	X,
	Y,
	Z
};
class Transform
{
public:
	mf::Vector3 position;
	mf::Vector3 rotation;
	mf::Vector3 scale;



	Transform() :position(0.0f), rotation(0.0f), scale(1.0f)
	{

	}

	void Translate(mf::Vector3 &translation)
	{
		position += translation;
	}
	void Translate(mf::Vector3 &translation, Space relativeTo = Space::Self)
	{
		switch (relativeTo)
		{
		case Space::Self:
			position += translation;
			break;
		case Space::World:

			break;
		default:
			break;
		}

	}

	void Rotate(float x, float y, float z)
	{
		rotation.x += mf::radians(x);
		rotation.y += mf::radians(y);
		rotation.z += mf::radians(z);
	}
	void Rotate(float value, Axis axis)
	{
		switch (axis)
		{
		case Axis::X:
			rotation.x += mf::radians(value);
			break;
		case Axis::Y:
			rotation.y += mf::radians(value);
			break;
		case Axis::Z:
			rotation.z += mf::radians(value);
			break;
		default:
			break;
		}

	}
	void Scale(float x, float y, float z)
	{
		scale.x *= x;
		scale.y *= y;
		scale.z *= z;
	}

	void Scale(mf::Vector3 &value)
	{
		scale = value;
	}

	mf::Vector3 ToWorld()
	{
		mf::Matrix4x4 otw = mf::Scale(scale)*mf::Rotate(rotation)*mf::Translation(position);

		return mf::TransformCoordinate(position, otw);
	}
	mf::Matrix4x4 ToWorldMatrix()
	{
		mf::Matrix4x4 otw = mf::Scale(scale)*mf::Rotate(rotation)*mf::Translation(position);
		return otw;
	}
private:

};
