#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "InputControl.h"
#include "PointsRepository.h"

class Pointer
{
private:
public:
	Pointer();
	~Pointer();
	void render(GLuint texture, GLint modelLoc);
};

