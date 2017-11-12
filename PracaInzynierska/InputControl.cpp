#include "InputControl.h"
#include <iostream>
Camera InputControl::camera = Camera(glm::vec3(0.28f, 1.05f, -0.12f));
bool InputControl::firstMove = true;
float InputControl::deltaTime = 0.0f;
float InputControl::lastFrame = 0.0f;

void InputControl::doMovement() {
	// Camera controls
	if (Keyboard::keys[GLFW_KEY_W])
	{
		InputControl::camera.ProcessKeyboard(FORWARD, deltaTime);
	}

	if (Keyboard::keys[GLFW_KEY_S])
	{
		InputControl::camera.ProcessKeyboard(BACKWARD, deltaTime);
	}

	if (Keyboard::keys[GLFW_KEY_A])
	{
		InputControl::camera.ProcessKeyboard(LEFT, deltaTime);
	}

	if (Keyboard::keys[GLFW_KEY_D])
	{
		InputControl::camera.ProcessKeyboard(RIGHT, deltaTime);
	}
}

void InputControl::keyCallback(GLFWwindow* window,
								int key,
								int scancode,
								int action,
								int mode) {
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (GLFW_KEY_UP == key)
	{
		dronePosition::pos_object_x -= 20;
	}
	if (GLFW_KEY_DOWN == key)
	{
		dronePosition::pos_object_x += 20;
	}
	if (GLFW_KEY_RIGHT == key)
	{
		dronePosition::pos_object_y -= 20;
	}
	if (GLFW_KEY_LEFT == key)
	{
		dronePosition::pos_object_y += 20;
	}
	if (GLFW_KEY_5 == key) {
		std::cout << "[DRONE REAL INFO] " << std::endl << "X: " << dronePosition::pos_object_x << std::endl << "Y: " << dronePosition::pos_object_y << std::endl;
		std::cout << "[DRONE OPENGL INFO] " << std::endl << "X: " << (dronePosition::pos_object_x - 692333) / MapData::scaleX << std::endl << "Y: " << (210568 - dronePosition::pos_object_y) / MapData::scaleY << std::endl;
		std::cout << "[CAMERA INFO] " << std::endl << "X: " << Camera::cameraLastX << std::endl << "Y: " << Camera::cameraLastY << std::endl;
		std::cout << "[CAMERA POSITION X] " << camera.GetPosition().x << std::endl;
		std::cout << "[CAMERA POSITION Y] " << camera.GetPosition().y << std::endl;
		std::cout << "[CAMERA POSITION Z] " << camera.GetPosition().z << std::endl;
		//std::cout << "[CAMERA POSITION YAW] " << camera.GetYaw() << std::endl;
		//std::cout << "[CAMERA POSITION PITCH] " << camera.GetPitch() << std::endl;

	}
	if (GLFW_KEY_SPACE == key) {
		PointsRepository* pointsRepository = new PointsRepository();
		CheckPoint point((dronePosition::pos_object_x - Setup::startingPointX) / MapData::scaleX,
						0,
			(Setup::startingPointY - dronePosition::pos_object_y) / MapData::scaleY);
		pointsRepository->addPoint(point);
		std::cout << "[POINTS AMOUNT] " << pointsRepository->getPointsVector().size() << std::endl;
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			Keyboard::keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			Keyboard::keys[key] = false;
		}
	}
}

void InputControl::mouseCallback(GLFWwindow * window,
								double xPos,
								double yPos) {
	GLfloat xOffset = xPos - Camera::cameraLastX;
	GLfloat yOffset = Camera::cameraLastY - yPos;  // Reversed since y-coordinates go from bottom to left
	Camera::cameraLastX = xPos;
	Camera::cameraLastY = yPos;
	if (InputControl::firstMove) {
		InputControl::camera.ProcessMouseMovement(0, 0);
		InputControl::firstMove = false;
	}
	else {
		InputControl::camera.ProcessMouseMovement(xOffset, yOffset);
	}
}
