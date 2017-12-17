#pragma once
#include <GL/glew.h>
#include <vector>
#define GLEW_STATIC
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const GLfloat YAW        = -180.75f;
const GLfloat PITCH      = -43.5f;
const GLfloat SPEED      =  3.0f;
const GLfloat SENSITIVTY =  0.25f;
const GLfloat ZOOM       =  45.0f;

class Camera
{
public:
	static float cameraLastX;
	static float cameraLastY;

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
    
    
	glm::mat4 GetViewMatrix();
 
	void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);
    void ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true);
    void ProcessMouseScroll(GLfloat yOffset);
	GLfloat GetZoom();
	glm::vec3 GetPosition();
	glm::vec3 GetFront();
	GLfloat GetYaw();
	GLfloat GetPitch();
	void SetYaw(GLfloat yaw);
	void SetPitch(GLfloat pitch);

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
       
    GLfloat yaw;
    GLfloat pitch;
    
    GLfloat movementSpeed;
    GLfloat mouseSensitivity;
    GLfloat zoom;
    
	void updateCameraVectors();
};
