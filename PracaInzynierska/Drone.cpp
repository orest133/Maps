/*
#include "Drone.h"


void Drone::drow(glm::mat4 model, GLint modelLoc) {
	//початок малювання літачка 
	float object_x = -0.415300548; //
	float object_y = -0.0985180512; //
									//glBindTexture(GL_TEXTURE_2D, airplaneTexture);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	model = glm::translate(model, glm::vec3(object_x, object_y, 0));
	model = glm::scale(model, glm::vec3(0.001f, 0.001f, 0.001f));
	model = glm::rotate(model, 1.59f, glm::vec3(-1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, 1.59f, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
};

float Drone::position_object_x() {
	return 0;// (dronePosition::pos_object_x - 692333) / (worldMapCoordinate[1].getTopRightX() - worldMapCoordinate[1].getTopLeftX());
};
float Drone::position_object_y() {
	return 0; // (210568 - dronePosition::pos_object_y) / (worldMapCoordinate[1].getBottomLeftY() - worldMapCoordinate[1].getTopLeftY());
};
Model Drone::getDrone() {
	return model;
};
*/