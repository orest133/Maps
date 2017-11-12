#pragma once
#include "dronePosition.h"
#include "Model.h"
#include "MapData.h"
class Drone
{
public:
	Drone():model("res/models/AR_Drone.obj") {};
	void draw(glm::mat4 model, GLint modelLoc, GLuint airplaneTexture){
			//початок малювання літачка 
			float object_x = position_object_x(); //
			float object_y = position_object_y(); //
			glBindTexture(GL_TEXTURE_2D, airplaneTexture);
			model = glm::translate(model, glm::vec3(object_x, object_y, 0));
			model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
			model = glm::rotate(model, 1.59f, glm::vec3(-1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, 1.59f, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		};
	Model getDroneModel() {
		return model;
	};
private:
	double height;
	double direction;

	Model model;
	float position_object_x() {
		return  (dronePosition::pos_object_x - 692333) / MapData::scaleX;
	};
	float  position_object_y() {
		return  (210568 - dronePosition::pos_object_y) / MapData::scaleY;
	};
	
};

