﻿/*
#include "Drone.h"



void Drone::draw(glm::mat4 model, GLint modelLoc, GLuint airplaneTexture) {
	//початок малювання літачка 
	float object_x = position_object_x(); //
	float object_y = position_object_y(); //
	float height = height_object();
	float direction = direction_object();
	glBindTexture(GL_TEXTURE_2D, airplaneTexture);
	model = glm::translate(model, glm::vec3(object_x, object_y, -height));
	model = glm::scale(model, glm::vec3(0.007f, 0.007f, 0.007f));
	model = glm::rotate(model, 1.59f, glm::vec3(-1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, direction, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
};

Model Drone::getDroneModel() {
	return model;
};

double Drone::quantifyPosition(double tmpTime) {
	if (tmpTime + 0.01 < glfwGetTime()) {
		tmpTime = glfwGetTime();
		if (Setup::positionXFromFile.size() > 1) {
			dronePosition::pos_object_x = Setup::positionXFromFile[Setup::positionXFromFile.size() - 1];
			Setup::positionXFromFile.pop_back();
			dronePosition::pos_object_y = Setup::positionYFromFile[Setup::positionYFromFile.size() - 1];
			Setup::positionYFromFile.pop_back();
			dronePosition::direction = Setup::positionDFromFile[Setup::positionYFromFile.size() - 1];
			Setup::positionDFromFile.pop_back();
			dronePosition::height = Setup::positionHFromFile[Setup::positionYFromFile.size() - 1];
			Setup::positionHFromFile.pop_back();
		}

	}
	return tmpTime;
};

float Drone::getHeight() {
	return height_object();
};
float Drone::getDirection() {
	return direction_object();
}


	float Drone::position_object_x() {
		return  (dronePosition::pos_object_x - Setup::startingPointX) / MapData::scaleX;
	};
	float  Drone::position_object_y() {
		return  (Setup::startingPointY - dronePosition::pos_object_y) / MapData::scaleY;
	};
	float Drone::height_object() {
		return dronePosition::height;
	}
	float Drone::direction_object() {
		return dronePosition::direction;
	}*/