#include "InputControl.h"
#include <iostream>
Camera InputControl::camera = Camera(glm::vec3(0.28f, 1.05f, -0.12f));
bool InputControl::firstMove = true;
float InputControl::deltaTime = 0.0f;
float InputControl::lastFrame = 0.0f;
//ofstream InputControl::myfile;

void InputControl::doMovement() {
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
	float step = 0.01f;
	PointsRepository* pointsRepository = new PointsRepository();
	//std::cout << "[DRONE REAL INFO] " << std::endl << "X: " << dronePosition::pos_object_x << std::endl << "Y: " << dronePosition::pos_object_y << std::endl << "H: " << dronePosition::height << std::endl << "D: " << dronePosition::direction << std::endl;
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (pointsRepository->getPointsVector().size() > 0 && !pointsRepository->getEditingMode()) {
		switch (key)
		{
		case GLFW_KEY_UP:
			if (action == GLFW_PRESS)
			{
				pointsRepository->setPointer(pointsRepository->getPointer() + 1);
			}
			break;
		case GLFW_KEY_DOWN:
			if (action == GLFW_PRESS)
			{
				pointsRepository->setPointer(pointsRepository->getPointer() - 1);
			}
			break;
		case GLFW_KEY_DELETE:
			if (action == GLFW_PRESS)
			{
				if (pointsRepository->getPointsVector().size() > 0) {
					int deletedIndex = pointsRepository->getPointer();
					if (deletedIndex != 0) {
						pointsRepository->setPointer(deletedIndex - 1);
					}
					else {
						pointsRepository->setPointer(0);
					}
					pointsRepository->removePoint(deletedIndex);
				}
			}
			break;
		case GLFW_KEY_KP_8:
			pointsRepository->getPointsVector().at(pointsRepository->getPointer()).setX(
				pointsRepository->getPointsVector().at(pointsRepository->getPointer()).getX() + step);
			break;
		case GLFW_KEY_KP_7:
			pointsRepository->getPointsVector().at(pointsRepository->getPointer()).setX(
				pointsRepository->getPointsVector().at(pointsRepository->getPointer()).getX() - step);
			break;
		case GLFW_KEY_KP_5:
			pointsRepository->getPointsVector().at(pointsRepository->getPointer()).setY(
				pointsRepository->getPointsVector().at(pointsRepository->getPointer()).getY() + step);
			break;
		case GLFW_KEY_KP_4:
			pointsRepository->getPointsVector().at(pointsRepository->getPointer()).setY(
				pointsRepository->getPointsVector().at(pointsRepository->getPointer()).getY() - step);
			break;
		case GLFW_KEY_KP_2:
			pointsRepository->getPointsVector().at(pointsRepository->getPointer()).setZ(
				pointsRepository->getPointsVector().at(pointsRepository->getPointer()).getZ() + step);
			break;
		case GLFW_KEY_KP_1:
			pointsRepository->getPointsVector().at(pointsRepository->getPointer()).setZ(
				pointsRepository->getPointsVector().at(pointsRepository->getPointer()).getZ() - step);
			break;
		default:
			break;
		}
	}
	if (GLFW_KEY_ENTER == key && action == GLFW_PRESS && pointsRepository->getPointsVector().size() > 0) {
		pointsRepository->setEditingMode(true);
	}
	if (GLFW_KEY_5 == key && action == GLFW_PRESS) {
		std::cout << "----------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "[DRONE REAL INFO] " << std::endl << "X: " << dronePosition::pos_object_x << std::endl << "Y: " << dronePosition::pos_object_y << std::endl;
		std::cout << "[DRONE OPENGL INFO] " << std::endl << "X: " << (dronePosition::pos_object_x - 692333) / MapData::scaleX << std::endl << "Y: " << (210568 - dronePosition::pos_object_y) / MapData::scaleY << std::endl;
		std::cout << "[CAMERA INFO] " << std::endl << "X: " << Camera::cameraLastX << std::endl << "Y: " << Camera::cameraLastY << std::endl;
		std::cout << "[CAMERA POSITION X] " << camera.GetPosition().x << std::endl;
		std::cout << "[CAMERA POSITION Y] " << camera.GetPosition().y << std::endl;
		std::cout << "[CAMERA POSITION Z] " << camera.GetPosition().z << std::endl;
		std::cout << "[CAMERA POSITION YAW] " << camera.GetYaw() << std::endl;
		std::cout << "[CAMERA POSITION PITCH] " << camera.GetPitch() << std::endl;
		std::cout << "----------------------------------------------------------------------------------------------------------" << std::endl;
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

void InputControl::mousePosCallback(GLFWwindow * window,
								double xPos,
								double yPos) {
	PointsRepository* pointsRepository = new PointsRepository();
	if (!pointsRepository->getEditingMode()) {
		GLfloat xOffset = xPos - Camera::cameraLastX;
		GLfloat yOffset = Camera::cameraLastY - yPos;
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
}

void InputControl::mouseClickCallback(GLFWwindow * window,
										int button,
										int action,
										int modifier) {
	PointsRepository* pointsRepository = new PointsRepository();
	if (!pointsRepository->getEditingMode()) {
		if (GLFW_MOUSE_BUTTON_LEFT == button && GLFW_RELEASE == action) {
			CheckPoint point(InputControl::camera.GetPosition().x,
				0.3f,
				InputControl::camera.GetPosition().z);
			pointsRepository->addPoint(point);
			std::cout << "[POINTS AMOUNT] " << pointsRepository->getPointsVector().size() << std::endl;
		}
		if (GLFW_MOUSE_BUTTON_RIGHT == button && GLFW_RELEASE == action) {
			if (pointsRepository->getPointsVector().size() > 0) {
				int deletedIndex = pointsRepository->getPointer();
				if (deletedIndex != 0) {
					pointsRepository->setPointer(deletedIndex - 1);
				}
				else {
					pointsRepository->setPointer(0);
				}
				pointsRepository->removePoint(deletedIndex);
			}
			std::cout << "[POINTS AMOUNT] " << pointsRepository->getPointsVector().size() << std::endl;
		}
	}
}

