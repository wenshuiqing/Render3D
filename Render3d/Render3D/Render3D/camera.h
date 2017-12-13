#pragma once

#include <vector>
#include "rmathf.h"
#include "transform.h"
#include "screen.h"
enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVTY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
private:
	mf::Vector3 WorldUp;
public:
	mf::Vector3 ZFront;
	mf::Vector3 Up;
	mf::Vector3 Right;
	Transform *transform;
	mf::Vector3 Position;

	float width;
	float height;
	float fov;
	float nearClip;
	float farClip;



	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;


public:
	Camera(mf::Vector3 position = mf::Vector3(0.0f, -3.0f, -20.0f), mf::Vector3 rotation = mf::Vector3(-10.0f, 0.0f, 0.0f)) : MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
	{
		SetFrustum(55.0f, (float)Screen::Width, (float)Screen::Height, 0.1f, 100.0f);
		WorldUp = mf::Vector3(0.0f, 1.0f, 0.0f);
		ZFront = mf::Vector3(0.0f, 0.0f, 1.0f);
		transform = new Transform;
		transform->position = position;
		transform->rotation = rotation;
		updateCameraVectors();
	}

	void SetFrustum(float fov, float width,float height,float nearClip,float farClip)
	{
		this->fov = fov;
		this->width = width;
		this->height = height;
		this->nearClip = nearClip;
		this->farClip = farClip;
	}

	mf::Matrix4x4 GetViewMatrix()
	{
		return mf::LookAtLH(transform->position, transform->position + ZFront, WorldUp);
	}

	mf::Matrix4x4 GetProjectionMatrix()
	{
		return mf::PerspectiveFovLH(mf::radians(fov), (float)width / (float)height, nearClip, farClip );
	}

	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		float velocity = MovementSpeed * deltaTime;
		if (direction == FORWARD)
			transform->position += ZFront * velocity;
		if (direction == BACKWARD)
			transform->position -= ZFront * velocity;
		if (direction == LEFT)
			transform->position -= Right * velocity;
		if (direction == RIGHT)
			transform->position += Right * velocity;
	}
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
	{
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		transform->rotation.y += xoffset;
		transform->rotation.x += yoffset;

		if (constrainPitch)
		{
			if (transform->rotation.x > 89.0f)
				transform->rotation.x = 89.0f;
			if (transform->rotation.x < -89.0f)
				transform->rotation.x = -89.0f;
		}

		updateCameraVectors();
	}

	void ProcessMouseScroll(float yoffset)
	{
		if (Zoom >= 1.0f && Zoom <= 45.0f)
			Zoom -= yoffset;
		if (Zoom <= 1.0f)
			Zoom = 1.0f;
		if (Zoom >= 45.0f)
			Zoom = 45.0f;
	}
	virtual ~Camera()
	{
		delete transform;
		transform = nullptr;
	}

private:
	void updateCameraVectors()
	{
		mf::Vector3 front;
		front.x = sin(mf::radians(transform->rotation.y));
		front.y = -sin(mf::radians(transform->rotation.x)) * cos(mf::radians(transform->rotation.y));
		front.z = cos(mf::radians(transform->rotation.y)) * cos(mf::radians(transform->rotation.x));

		ZFront = mf::Normalize(front);
		Right = mf::Normalize(mf::Cross(WorldUp, ZFront));
		Up = mf::Normalize(mf::Cross(ZFront, Right));
	}
};

