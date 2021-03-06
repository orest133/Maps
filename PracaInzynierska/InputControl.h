#pragma once
#include "Camera.h"
#include "Keyboard.h"
#include "dronePosition.h"
#include "PointsRepository.h"
#include <iostream>
#include <fstream>
// GLFW
#include <GLFW/glfw3.h>
class InputControl {
public:
	
	static Camera camera;
	static bool firstMove;
	static float deltaTime;
	static float lastFrame;
	static void doMovement();
//	static ofstream myfile;
	static void keyCallback(GLFWwindow* window,
							int key,
							int scancode,
							int action,
							int mode);
	static void mousePosCallback(GLFWwindow *window,
							double xPos,
							double yPos);
	static void mouseClickCallback(GLFWwindow *window,
							int button,
							int action,
							int modifier);
};

