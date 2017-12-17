#pragma once
// Std. Includes
#include <ft2build.h>
#include FT_FREETYPE_H
//#include <string>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"
#include "InputControl.h"
#include "dronePosition.h"
#include "getResolution.h"
#include "PointsRepository.h"
#include "TrajectoryPointsRepository.h"
#include "Drone.h"
#include "MapData.h"
#include "Pointer.h"
#include "Trajectory.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SOIL2/SOIL2.h"

#include "Text.h"


int SCREEN_WIDTH = 0, SCREEN_HEIGHT = 0;


void  drowLine(glm::mat4 model, GLint modelLoc, int pointsCount, GLfloat *lineVertices, int lineVerticesSize) {
	GLuint vao;
	GLuint vbo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, lineVerticesSize * sizeof(GLfloat), lineVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
	glBindVertexArray(0);

	glBindVertexArray(vao);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_LINE_STRIP, 0, pointsCount);
	glBindVertexArray(0);
}

int main() {
	Setup::loadDate();

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	getResolution::GetDesktopResolution(SCREEN_HEIGHT, SCREEN_WIDTH);
	GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH/1.7, SCREEN_HEIGHT/ 1.7, "Ivan Sopyliuk", nullptr, nullptr);
	if (nullptr == window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	glfwSetKeyCallback(window, &InputControl::keyCallback);
	glfwSetCursorPosCallback(window, &InputControl::mousePosCallback);
	glfwSetMouseButtonCallback(window, &InputControl::mouseClickCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_DEPTH_TEST);

	PointsRepository* pointsRepository = new PointsRepository();
	Pointer* pointer = new Pointer();
	MapData mapData;
	Drone drone;
	TrajectoryPointsRepository *pointsRepositoryTrajectory = new TrajectoryPointsRepository();

	GLfloat vertices[] = {
		// Positions          // Colors           // Texture Coords
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // x=0,y=0
		0.0f, -1.f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, //x=0,y=-1
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //x=-1,y=-1
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // x=0,y=0
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //x=-1,y=-1
		-1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //x=0,y=-1
	};

	GLfloat skyboxVertices[] = {
		// Positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};
	
	Shader shader("res/shaders/cube.vs", "res/shaders/cube.frag");
	Shader airplaneShader("res/shaders/modelLoading.vs", "res/shaders/modelLoading.frag");
	Shader skyboxShader("res/shaders/skybox.vs", "res/shaders/skybox.frag");
	Shader linesShader("res/shaders/lines.vs", "res/shaders/lines.frag");
	Shader *shaderText= new Shader("res/shaders/text.vs", "res/shaders/text.frag");

	GLuint cubeVAO, cubeVBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
	glBindVertexArray(0);

	// Setup skybox VAO
	GLuint skyboxVAO, skyboxVBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
	glBindVertexArray(0);

	// Setup points VAO
	glGenVertexArrays(1, &pointsRepository->VAO);
	glGenBuffers(1, &pointsRepository->VBO);
	glBindVertexArray(pointsRepository->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, pointsRepository->VBO);
	glBufferData(GL_ARRAY_BUFFER, pointsRepository->getVerticlesSizeForCube(), pointsRepository->getPointVerticles(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Setup points VAO
	glGenVertexArrays(1, &pointsRepositoryTrajectory->VAO);
	glGenBuffers(1, &pointsRepositoryTrajectory->VBO);
	glBindVertexArray(pointsRepositoryTrajectory->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, pointsRepositoryTrajectory->VBO);
	glBufferData(GL_ARRAY_BUFFER, pointsRepositoryTrajectory->getVerticlesSizeForCube(), pointsRepositoryTrajectory->getPointVerticles(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// Cubemap (Skybox)
	vector<const GLchar*> faces;
	// Load textures
	faces.push_back("res/images/right.bmp");
	faces.push_back("res/images/left.bmp");
	faces.push_back("res/images/top.bmp");
	faces.push_back("res/images/bottom.bmp");
	faces.push_back("res/images/front.bmp");
	faces.push_back("res/images/back.bmp");
	vector<GLuint> textureMap;

	for (vector<WorldMapCoordinates>::iterator map = mapData.worldMapCoordinate.begin(); map != mapData.worldMapCoordinate.end(); ++map) {
		string path=map->getPatchTexture();
		path=path.substr(0, path.find(".tif")) + ".png";
		textureMap.push_back(TextureLoading::LoadTexture(path.c_str()));
		}
	GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);
	GLuint cubeTexture = TextureLoading::LoadTexture("res/images/triangle.png");
	GLuint textureTrajectory = TextureLoading::LoadTexture("res/images/textureTrajectory.jpg");
	GLuint airplaneTexture = TextureLoading::LoadTexture("res/models/texture.png");
	float j = 0;

	double tmpTime = glfwGetTime();
	double tmpTime2 = glfwGetTime();
	
	Text text;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	text.loadTexture();
	while (!glfwWindowShouldClose(window))
	{
		tmpTime2= drone.quantifyPosition(tmpTime2);

		// Set frame time
		GLfloat currentFrame = glfwGetTime();
		InputControl::deltaTime = currentFrame - InputControl::lastFrame;
		InputControl::lastFrame = currentFrame;
		InputControl::doMovement();
		// Set variables
		glm::mat4 model;
		glm::mat4 view = InputControl::camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(InputControl::camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f);
		GLint modelLoc = glGetUniformLocation(shader.Program, "model");
		GLint viewLoc = glGetUniformLocation(shader.Program, "view");
		GLint projLoc = glGetUniformLocation(shader.Program, "projection");
		// Check and call events
		glfwPollEvents();
		// Clear the colorbuffer
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.Use();
		glActiveTexture(GL_TEXTURE0);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		//Start draw maps
		glBindVertexArray(cubeVAO);
		model = glm::rotate(model, 1.5708f, glm::vec3(1.0f, 0.0f, 0.0f));
		int i = 0;
		for (vector<WorldMapCoordinates>::iterator map = mapData.worldMapCoordinate.begin(); map != mapData.worldMapCoordinate.end(); ++map, i++)
			mapData.drowMap(map->getCoordinateX(), map->getCoordinateY(), model, modelLoc, textureMap[i]);
		glBindVertexArray(0);
		//End draw maps
		
		//Points start
		glBindVertexArray(pointsRepository->VAO);
		int pointsVectorSize = pointsRepository->getPointsVector().size();
		int arraySize = pointsVectorSize * 3;
		GLfloat *lineVertices = new GLfloat[arraySize]();
		for (unsigned int i = 0; i < pointsVectorSize; i++) {
			glm::mat4 point;
			glBindTexture(GL_TEXTURE_2D, cubeTexture);
			point = glm::translate(point, glm::vec3(pointsRepository->getPointsVector().at(i).getX(),
				pointsRepository->getPointsVector().at(i).getY(),
				pointsRepository->getPointsVector().at(i).getZ()));
			point = glm::scale(point, glm::vec3(0.05f, 0.05f, 0.05f));
			point = glm::rotate(point, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(point));
			glDrawArrays(GL_TRIANGLES, 0, 36);
			int j = i*3;
			lineVertices[j] = pointsRepository->getPointsVector().at(i).getX();
			lineVertices[j + 1] = pointsRepository->getPointsVector().at(i).getZ();
			lineVertices[j + 2] = -pointsRepository->getPointsVector().at(i).getY();
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		//Points end
		drowLine(model, modelLoc, pointsVectorSize, lineVertices, arraySize);
		delete[] lineVertices;
		//CameraPointer start
		glBindVertexArray(pointsRepository->VAO);
		glm::mat4 point;
		glBindTexture(GL_TEXTURE_2D, cubeTexture);
		point = glm::translate(point, glm::vec3(InputControl::camera.GetPosition().x,
			0.5f,
			InputControl::camera.GetPosition().z));
		point = glm::scale(point, glm::vec3(0.03f, 0.03f, 0.03f));
		point = glm::rotate(point, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(point));
		glDrawArrays(GL_TRIANGLES, 0, 36);		
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		//CameraPointer end
		
		//Points Trajectory start
		glBindVertexArray(pointsRepositoryTrajectory->VAO);
		tmpTime = Trajectory::drow(tmpTime, model, modelLoc, textureTrajectory, pointsRepositoryTrajectory);
		glBindVertexArray(0);
		//Points Trajectory end 

		//Start draw airplane 
		airplaneShader.Use();
		glUniformMatrix4fv(glGetUniformLocation(airplaneShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(airplaneShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		drone.draw(model, modelLoc, airplaneTexture);
		drone.getDroneModel().Draw(shader);
		//end draw airplane
		
		// start drow CubMap
		glDepthFunc(GL_LEQUAL); 
		skyboxShader.Use();
		view = glm::mat4(glm::mat3(InputControl::camera.GetViewMatrix()));	
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(skyboxVAO);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); 
	   // end drow CubMap
	
	  //start draw text
		text.RenderText(shaderText, "Position X: " + to_string((int)dronePosition::pos_object_x), 0.0f, 10.0f, 0.5f, glm::vec3(20.0f, 0.8f, 0.2f));
		text.RenderText(shaderText, "Position Y: " + to_string((int)dronePosition::pos_object_y), 0.0f, 30.0f, 0.5f, glm::vec3(40.0f, 0.8f, 0.2f));
		text.RenderText(shaderText, "Direction: " + to_string((int)(dronePosition::direction*100)), 0.0f, 50.0f, 0.5f, glm::vec3(50.0f, 0.8f, 0.2f));
		text.RenderText(shaderText, "Height Y: " + to_string((int)(dronePosition::height*100)), 0.0f, 70.0f, 0.5f, glm::vec3(60.0f, 0.8f, 0.2f));
		text.RenderText(shaderText, " ", 0.5f, 0.0f, 0.5f, glm::vec3(20.0f, 0.8f, 0.2f));
		//end draw text
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

