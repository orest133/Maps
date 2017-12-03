#include "Pointer.h"



Pointer::Pointer()
{
}


Pointer::~Pointer()
{
}

void Pointer::render(GLuint texture, GLint modelLoc) {
	std::cout << "texture:" << texture << std::endl;
	std::cout << "modelLoc:" << modelLoc << std::endl;
	glm::mat4 point;
	glBindTexture(GL_TEXTURE_2D, texture);
	point = glm::translate(point, glm::vec3(InputControl::camera.GetPosition().x,
		0.5,
		InputControl::camera.GetPosition().z));
	point = glm::scale(point, glm::vec3(0.03f, 0.03f, 0.03f));
	point = glm::rotate(point, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(point));
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
