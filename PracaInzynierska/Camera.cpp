#include "Camera.h"
float Camera::cameraLastX = 0;
float Camera::cameraLastY = 0;

glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(this->position, this->position + this->front, this->up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime) {
	GLfloat velocity = (this->movementSpeed * deltaTime)/2;

	if (direction == FORWARD)
	{
		this->position += this->front * velocity;
	}

	if (direction == BACKWARD)
	{
		this->position -= this->front * velocity;
	}

	if (direction == LEFT)
	{
		this->position -= this->right * velocity;
	}

	if (direction == RIGHT)
	{
		this->position += this->right * velocity;
	}
}

void Camera::ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch) {
	xOffset *= this->mouseSensitivity;
	yOffset *= this->mouseSensitivity;

	this->yaw += xOffset;
	this->pitch += yOffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (this->pitch > 89.0f)
		{
			this->pitch = 89.0f;
		}

		if (this->pitch < -89.0f)
		{
			this->pitch = -89.0f;
		}
	}

	// Update Front, Right and Up Vectors using the updated Eular angles
	this->updateCameraVectors();
}

void Camera::ProcessMouseScroll(GLfloat yOffset)
{
}

GLfloat Camera::GetZoom() {
	return this->zoom;
}

glm::vec3 Camera::GetPosition() {
	return this->position;
}

glm::vec3 Camera::GetFront() {
	return this->front;
}

GLfloat Camera::GetYaw()
{
	return this->yaw;
}

GLfloat Camera::GetPitch()
{
	return this->pitch;
}

void Camera::SetYaw(GLfloat yaw)
{
	this->yaw = yaw;
}

void Camera::SetPitch(GLfloat pitch)
{
	this->pitch = pitch;
}

void Camera::updateCameraVectors() {
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	front.y = sin(glm::radians(this->pitch));
	front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	this->right = glm::normalize(glm::cross(this->front, this->worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	this->up = glm::normalize(glm::cross(this->right, this->front));
}
