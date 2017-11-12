#pragma once
#include "Camera.h"
#include "Keyboard.h"
#include "dronePosition.h"
#include "PointsRepository.h"

// GLFW
#include <GLFW/glfw3.h>
class InputControl {
public:
	static Camera camera;
	static bool firstMove;
	static float deltaTime;
	static float lastFrame;
	static void doMovement();
	static void keyCallback(GLFWwindow* window,
							int key,
							int scancode,
							int action,
							int mode);
	static void mouseCallback(GLFWwindow *window,
							double xPos,
							double yPos);
};

