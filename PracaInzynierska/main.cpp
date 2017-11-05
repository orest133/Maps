#pragma once
// Std. Includes
#include <string>
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
#include "WorldMapCoordinates.h"
#include "InputControl.h"
#include "dronePosition.h"
#include "getResolution.h"
// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// Other Libs
#include "SOIL2/SOIL2.h"

// Properties
int SCREEN_WIDTH = 0, SCREEN_HEIGHT = 0;

float static central_poxition_x = 689032;//Позиція вписана оператором ,точка відліку 
float static central_position_y = 212567;//Позиція вписана оператором ,точка відліку 

void  drowMap(float x, float  y, glm::mat4 model, GLint modelLoc, int index) {
	glBindTexture(GL_TEXTURE_2D, index);
	model = glm::translate(model, glm::vec3(x, y, 0));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 6);
}


int main()
{
	vector<WorldMapCoordinates> worldMapCoordinate;
	worldMapCoordinate.push_back(WorldMapCoordinates("maps/M-34-080-C-d-1-1.tif"));
	worldMapCoordinate.push_back(WorldMapCoordinates("maps/M-34-080-C-d-1-2.tif"));
	worldMapCoordinate.push_back(WorldMapCoordinates("maps/M-34-080-C-d-1-3.tif"));
	worldMapCoordinate.push_back(WorldMapCoordinates("maps/M-34-080-C-d-1-4.tif"));
	// Init GLFWs
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	getResolution::GetDesktopResolution(SCREEN_HEIGHT, SCREEN_WIDTH);
	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, "LearnOpenGL", nullptr, nullptr);
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
	// Set the required callback functions
	glfwSetKeyCallback(window, &InputControl::keyCallback);

	glfwSetCursorPosCallback(window, &InputControl::mouseCallback);
	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);

	// Setup and compile our shaders
	Shader shader("res/shaders/cube.vs", "res/shaders/cube.frag");
	Shader skyboxShader("res/shaders/skybox.vs", "res/shaders/skybox.frag");


	GLfloat vertices[] = {
		// Positions          // Colors           // Texture Coords
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // x=0,y=0
		0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, //x=0,y=-1
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

	// Load textures
	GLuint cubeTexture = TextureLoading::LoadTexture("res/images/container2.png");

	vector<GLuint> textureMap;
	textureMap.push_back(TextureLoading::LoadTexture("\maps/M-34-080-C-d-1-1.png"));
	textureMap.push_back(TextureLoading::LoadTexture("\maps/M-34-080-C-d-1-2.png"));
	textureMap.push_back(TextureLoading::LoadTexture("\maps/M-34-080-C-d-1-3.png"));
	textureMap.push_back(TextureLoading::LoadTexture("\maps/M-34-080-C-d-1-4.png"));


	// Cubemap (Skybox)
	vector<const GLchar*> faces;
	faces.push_back("res/images/right.bmp");
	faces.push_back("res/images/left.bmp");
	faces.push_back("res/images/top.bmp");
	faces.push_back("res/images/bottom.bmp");
	faces.push_back("res/images/front.bmp");
	faces.push_back("res/images/back.bmp");

	GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);

	GLuint airplaneTexture = TextureLoading::LoadTexture("res/models/texture.png");

	glm::mat4 projection = glm::perspective(InputControl::camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f);
	// Load models
	Model ourModel("res/models/airplane.obj");
	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Set frame time
		GLfloat currentFrame = glfwGetTime();
		InputControl::deltaTime = currentFrame - InputControl::lastFrame;
		InputControl::lastFrame = currentFrame;
		// Check and call events
		glfwPollEvents();
		InputControl::doMovement();
		// Clear the colorbuffer
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glm::mat4 model;
		glm::mat4 view = InputControl::camera.GetViewMatrix();
		// Draw our first triangle
		shader.Use();
		// Bind Textures using texture units
		glActiveTexture(GL_TEXTURE0);
		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(shader.Program, "model");
		GLint viewLoc = glGetUniformLocation(shader.Program, "view");
		GLint projLoc = glGetUniformLocation(shader.Program, "projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		//Початок малювання карт
		glBindVertexArray(cubeVAO);
		model = glm::rotate(model, 1.59f, glm::vec3(1.0f, 0.0f, 0.0f));
		int i = 0;
		for (vector<WorldMapCoordinates>::iterator map = worldMapCoordinate.begin(); map != worldMapCoordinate.end(); ++map, i++)
			drowMap(map->getCoordinateX(), map->getCoordinateY(), model, modelLoc, textureMap[i]);
		glBindVertexArray(0);
		//кінець малювання карт

		//початок малювання літачка 
		float object_x = (dronePosition::pos_object_x - 692333) / (worldMapCoordinate[1].getTopRightX() - worldMapCoordinate[1].getTopLeftX());
		float object_y = (210568 - dronePosition::pos_object_y) / (worldMapCoordinate[1].getBottomLeftY() - worldMapCoordinate[1].getTopLeftY());
		glBindTexture(GL_TEXTURE_2D, cubeTexture);
		glm::mat4  model2 = model;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		model2 = glm::translate(model2, glm::vec3(object_x, object_y, 0));
		model2 = glm::scale(model2, glm::vec3(0.001f, 0.001f, 0.001f));
		model2 = glm::rotate(model2, 1.59f, glm::vec3(-1.0f, 0.0f, 0.0f));
		model2 = glm::rotate(model2, 1.59f, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		ourModel.Draw(shader);
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

		// Swap the buffers
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

