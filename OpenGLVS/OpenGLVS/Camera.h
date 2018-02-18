#include <vector>

// GL Includes
#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Display.h"

using namespace std;

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 6.0f;
const GLfloat SENSITIVTY = 0.25f;
const GLfloat ZOOM = 45.0f;

#pragma once
class Camera {
public:
	GLfloat deltaTime = 0.0f;
	bool keys[1024];
	bool firstMouse = true;
	GLfloat lastX;
	GLfloat lastY;

	Camera(Display* display);

	void updateCameraVectors();
	glm::mat4 GetViewMatrix();
	void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);
	void ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(GLfloat yOffset);
	GLfloat GetZoom();

	void initCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);
	void initCamera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);

	void DoMovement(GLfloat deltaTime);
private:
	Display* display;

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
	
	void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
	void mouseCallback(GLFWwindow *window, double xPos, double yPos);
	void scrollCallback(GLFWwindow *window, double xOffset, double yOffset);
};