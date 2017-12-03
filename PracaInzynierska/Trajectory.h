#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include "TrajectoryPointsRepository.h"
#include "dronePosition.h"
#include <GLFW/glfw3.h>
// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Trajectory
{
public:
	Trajectory();
	~Trajectory();
	static float drow(float tmpTime, glm::mat4 model, GLint modelLoc, GLuint textureTrajectory, TrajectoryPointsRepository *pointsRepositoryTrajectory);

};

