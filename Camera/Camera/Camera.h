#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values 
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5F;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
	// camera attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// euler angles
	float Yaw;
	float Pitch;
	// camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	// constructor with vectors 
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) :
		Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED),
		MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		UpdateCameraVectors();
	}

	// constructor with scalar values 
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, 
		float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED),
		MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = glm::vec3(posX, posY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		UpdateCameraVectors();
	}

	// returns the view matrix calculated using Euler Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(Position, Position + Front, Up);
	}
	
	glm::mat4 GetCustomViewMatrix()
	{	
		glm::mat4 cameraRotMatrix = glm::mat4(1.0f);
		cameraRotMatrix[0][0] = Right.x;
		cameraRotMatrix[1][0] = Right.y;
		cameraRotMatrix[2][0] = Right.z;
		cameraRotMatrix[0][1] = Up.x;
		cameraRotMatrix[1][1] = Up.y;
		cameraRotMatrix[2][1] = Up.z;
		cameraRotMatrix[0][2] = -Front.x;
		cameraRotMatrix[1][2] = -Front.y;
		cameraRotMatrix[2][2] = -Front.z;

		glm::mat4 cameraTransMatrix = glm::mat4(1.0f);
		cameraTransMatrix[3][0] = -Position.x;
		cameraTransMatrix[3][1] = -Position.y;
		cameraTransMatrix[3][2] = -Position.z;

		return cameraRotMatrix * cameraTransMatrix;
	}

	// process input from keyboard 
	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		float velocity = MovementSpeed * deltaTime;
		if (direction == FORWARD)
			Position += Front * velocity;
		if (direction == BACKWARD)
			Position -= Front * velocity;
		if (direction == LEFT)
			Position -= Right * velocity;
		if (direction == RIGHT)
			Position += Right * velocity;
	}

	// process input from a mouse input system 
	void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true)
	{
		xOffset *= MouseSensitivity;
		yOffset *= MouseSensitivity;

		Yaw += xOffset;
		Pitch += yOffset;

		if (constrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}
		UpdateCameraVectors();
	}

	// process input from mouse scroll 
	void ProcessMouseScroll(float yOffset)
	{
		Zoom -= (float)yOffset;
		if (Zoom < 1.0f)
			Zoom = 1.0f;
		if (Zoom > 45.0f)
			Zoom = 45.0f;
	}

private:
	// calculate the fron vector from Camera's updated Euler Angles
	void UpdateCameraVectors()
	{
		// calculate new front vector
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);

		// re-calculate the right and up vector
		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}
};

#endif