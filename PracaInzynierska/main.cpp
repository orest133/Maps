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
// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// Other Libs
#include "SOIL2/SOIL2.h"

#include "Text.h"

// Properties
int SCREEN_WIDTH = 0, SCREEN_HEIGHT = 0;

float static central_poxition_x = 689032;//Позиція вписана оператором ,точка відліку 
float static central_position_y = 212567;//Позиція вписана оператором ,точка відліку 

void  drowMap(float x, float  y, glm::mat4 model, GLint modelLoc, int index) {
	glBindTexture(GL_TEXTURE_2D, index);
	model = glm::translate(model, glm::vec3(x, y, 0.0));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

int main() {
	Setup::loadDate();
	// Init GLFWs
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	// Create a GLFWwindow object that we can use for GLFW's functions
	getResolution::GetDesktopResolution(SCREEN_HEIGHT, SCREEN_WIDTH);
	GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (nullptr == window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
	// Set the required callback functions
	glfwSetKeyCallback(window, &InputControl::keyCallback);
	glfwSetCursorPosCallback(window, &InputControl::mousePosCallback);
	glfwSetMouseButtonCallback(window, &InputControl::mouseClickCallback);
	// GLFW Options
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}
	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	// OpenGL options
	glEnable(GL_DEPTH_TEST);

	//Creating general objects
	PointsRepository* pointsRepository = new PointsRepository();
	Pointer* pointer = new Pointer();
	MapData mapData;
	Drone drone;
	TrajectoryPointsRepository *pointsRepositoryTrajectory = new TrajectoryPointsRepository();
	//CONSTANTS
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
	//CONSTANTS END

	// Setup and compile our shaders
	Shader shader("res/shaders/cube.vs", "res/shaders/cube.frag");
	Shader airplaneShader("res/shaders/modelLoading.vs", "res/shaders/modelLoading.frag");
	Shader skyboxShader("res/shaders/skybox.vs", "res/shaders/skybox.frag");
	Shader *shaderText= new Shader("res/shaders/text.vs", "res/shaders/text.frag");
	// Setup cube VAO
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

	// Load textures
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
	// Game loop
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
		// Draw our first triangle
		shader.Use();
		// Bind Textures using texture units
		glActiveTexture(GL_TEXTURE0);
		// Get the uniform locations
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		//Початок малювання карт
		glBindVertexArray(cubeVAO);
		model = glm::rotate(model, 1.59f, glm::vec3(1.0f, 0.0f, 0.0f));
		int i = 0;
		for (vector<WorldMapCoordinates>::iterator map = mapData.worldMapCoordinate.begin(); map != mapData.worldMapCoordinate.end(); ++map, i++)
			drowMap(map->getCoordinateX(), map->getCoordinateY(), model, modelLoc, textureMap[i]);
		
		//кінець малювання карт

		//Points start
		glBindVertexArray(pointsRepository->VAO);
		for (unsigned int i = 0; i < pointsRepository->getPointsVector().size(); i++) {
			glm::mat4 point;
			glBindTexture(GL_TEXTURE_2D, cubeTexture);
			point = glm::translate(point, glm::vec3(pointsRepository->getPointsVector().at(i).getX(),
				pointsRepository->getPointsVector().at(i).getY(),
				pointsRepository->getPointsVector().at(i).getZ()));
				point = glm::scale(point, glm::vec3(0.03f, 0.03f, 0.03f));
			point = glm::rotate(point, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(point));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);
		//Points end
		//CameraPointer start
		glBindVertexArray(pointsRepository->VAO);
		glm::mat4 point;
		glBindTexture(GL_TEXTURE_2D, cubeTexture);
		point = glm::translate(point, glm::vec3(InputControl::camera.GetPosition().x,
			0.5,
			InputControl::camera.GetPosition().z));
		point = glm::scale(point, glm::vec3(0.03f, 0.03f, 0.03f));
		point = glm::rotate(point, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(point));
		glDrawArrays(GL_TRIANGLES, 0, 36);		
		glBindVertexArray(0);
		//CameraPointer end
		
		//Points Trajectory start
		glBindVertexArray(pointsRepositoryTrajectory->VAO);
		tmpTime = Trajectory::drow(tmpTime, model, modelLoc, textureTrajectory, pointsRepositoryTrajectory);
		glBindVertexArray(0);
		//Points Trajectory end 

		//початок малювання літачка 
		airplaneShader.Use();
		glUniformMatrix4fv(glGetUniformLocation(airplaneShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(airplaneShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		drone.draw(model, modelLoc, airplaneTexture);
		drone.getDroneModel().Draw(shader);
		//кінець малювання літака 

		// початок малювання оточення 
		glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
		skyboxShader.Use();
		view = glm::mat4(glm::mat3(InputControl::camera.GetViewMatrix()));	// Remove any translation component of the view matri
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(skyboxVAO);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // Set depth function back to default
	   // кінець малювання оточення 
		
	
		text.RenderText(shaderText, "Position X: " + to_string((int)dronePosition::pos_object_x), 0.0f, 10.0f, 0.5f, glm::vec3(20.0f, 0.8f, 0.2f));
		text.RenderText(shaderText, "Position Y: " + to_string((int)dronePosition::pos_object_y), 0.0f, 30.0f, 0.5f, glm::vec3(40.0f, 0.8f, 0.2f));
		text.RenderText(shaderText, "Direction: " + to_string((int)(dronePosition::direction*100)), 0.0f, 50.0f, 0.5f, glm::vec3(50.0f, 0.8f, 0.2f));
		text.RenderText(shaderText, "Height Y: " + to_string((int)(dronePosition::height*100)), 0.0f, 70.0f, 0.5f, glm::vec3(60.0f, 0.8f, 0.2f));
		text.RenderText(shaderText, " ", 0.5f, 0.0f, 0.5f, glm::vec3(20.0f, 0.8f, 0.2f));
		// Swap the buffers
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

