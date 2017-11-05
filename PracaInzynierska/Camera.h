#pragma once
#include <GL/glew.h>
// Std. Includes
#include <vector>
// GL Includes
#define GLEW_STATIC
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
//const GLfloat YAW        = -90.0f;
//const GLfloat PITCH      =  0.0f;
//const GLfloat SPEED      =  6.0f;
const GLfloat YAW        = -180.75f;
const GLfloat PITCH      = -43.5f;
const GLfloat SPEED      =  3.0f;
const GLfloat SENSITIVTY =  0.25f;
const GLfloat ZOOM       =  45.0f;

// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
	static float cameraLastX;
	static float cameraLastY;
    // Constructor with vectors
    Camera( glm::vec3 position = glm::vec3( 0.0f, 0.0f, 0.0f ),
			glm::vec3 up = glm::vec3( 0.0f, 1.0f, 0.0f ),
			GLfloat yaw = YAW, GLfloat pitch = PITCH ) : front( glm::vec3( 0.0f, 0.0f, -1.0f ) ),
			movementSpeed( SPEED ),
			mouseSensitivity( SENSITIVTY ),
			zoom( ZOOM ) {
        this->position = position;
        this->worldUp = up;
        this->yaw = yaw;
        this->pitch = pitch;
        this->updateCameraVectors( );
    }
    
    // Constructor with scalar values
    Camera( GLfloat posX,
			GLfloat posY,
			GLfloat posZ,
			GLfloat upX,
			GLfloat upY,
			GLfloat upZ,
			GLfloat yaw,
			GLfloat pitch ) : front( glm::vec3( 0.0f, 0.0f, -1.0f ) ),
			movementSpeed( SPEED ),
			mouseSensitivity( SENSITIVTY ),
			zoom( ZOOM ) {
        this->position = glm::vec3( posX, posY, posZ );
        this->worldUp = glm::vec3( upX, upY, upZ );
        this->yaw = yaw;
        this->pitch = pitch;
        this->updateCameraVectors( );
    }
    
    // Returns the view matrix calculated using Eular Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix();
    // Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);
    // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true);
    // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(GLfloat yOffset);
	GLfloat GetZoom();
	glm::vec3 GetPosition();
	glm::vec3 GetFront();
	GLfloat GetYaw();
	GLfloat GetPitch();
	void SetYaw(GLfloat yaw);
	void SetPitch(GLfloat pitch);

private:
    // Camera Attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    
    // Eular Angles
    GLfloat yaw;
    GLfloat pitch;
    
    // Camera options
    GLfloat movementSpeed;
    GLfloat mouseSensitivity;
    GLfloat zoom;
    
    // Calculates the front vector from the Camera's (updated) Eular Angles
	void updateCameraVectors();
};
