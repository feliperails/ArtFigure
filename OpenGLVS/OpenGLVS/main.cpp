// Std. Includes
#include <string>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#define _USE_MATH_DEFINES
#include <math.h>

// GL includes
#include "ShaderTest.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "soil.h"
#include "Display.h"
#include "Camera.h";
#include "Arm.h";
#include "ArtPicture.h";

#define MINIMUM_VALUE(x, y) ((x) < (y) ? (x) : (y))

// Properties

GLfloat lastFrame = 0.0f;

Camera* camera;

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void mouseCallback(GLFWwindow *window, double xPos, double yPos);
void scrollCallback(GLFWwindow *window, double xOffset, double yOffset);

float startAngle = 0;
float startTime;
float endTime;
float duration = 2;
float currentTime;
unsigned int movIndex = 0;
bool started = false;
vector<ArmMovement*>* movements;

int main()
{
	try
	{
		ArtPicture* artPicture = new ArtPicture();

		Arm* arm = new Arm();
		arm->add(new ArmPart(6, 0.0f, 0.0f, 0.0f, 1.0f));
		arm->add(new ArmPart(2, 0.0f, 1.0f, 0.0f, 1.0f));
		arm->add(new ArmPart(1, 0.0f, 0.0f, 1.0f, 1.0f));
		arm->setTarget(2, 7, 0);

		movements = arm->getMovements();

		glewExperimental = GL_TRUE;

		artPicture->setArm(arm);

		artPicture->build();

		Display* display = new Display();

		display->init(800, 600, "Figuras Articuladas");
		GLFWwindow* window = display->getWindow();

		camera = new Camera(display);

		// Set the required callback functions
		glfwSetKeyCallback(display->getWindow(), keyCallback);
		// glfwSetCursorPosCallback(display->getWindow(), mouseCallback);
		glfwSetScrollCallback(display->getWindow(), scrollCallback);

		display->initGL();

		// Setup and compile our shaders
		ShaderTest ourShader("res/shaders/core.vs", "res/shaders/core.fs");

		GLfloat target[] = { 2.0f, 2.0f };

		glm::vec3 cubePositions[] =
		{
			glm::vec3(0.0f, 0.0f, 0.0f)
			, glm::vec3(2.0f, 2.0f, 0.0f)
			, glm::vec3(4.0f, 4.0f, 0.0f)
			, glm::vec3(-3.8f, -2.0f, -12.3f)
			, glm::vec3(2.4f, -0.4f, -3.5f)
			, glm::vec3(-1.7f, 3.0f, -7.5f)
			, glm::vec3(1.3f, -2.0f, -2.5f)
			, glm::vec3(1.5f, 2.0f, -2.5f)
			, glm::vec3(1.5f, 0.2f, -1.5f)
			, glm::vec3(-1.3f, 1.0f, -1.5f)
		};

		artPicture->initMesh();

		vector<Mesh*> meshList = *artPicture->getMeshList();

		while (!glfwWindowShouldClose(window))
		{
			// Set frame time
			currentTime = glfwGetTime();
			lastFrame = currentTime;
			
			if (!started) {
				started = true;
				startTime = currentTime;
				endTime = startTime + duration;
			}

			// Check and call events
			glfwPollEvents();
			camera->DoMovement(currentTime - lastFrame);

			// Clear the colorbuffer
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Draw our first triangle
			ourShader.Use();

			glm::mat4 projection;
			projection = glm::perspective(camera->GetZoom(), (GLfloat)display->screenWidth / (GLfloat)display->screenHeight, 0.1f, 1000.0f);

			// Create camera transformation
			glm::mat4 view;
			view = camera->GetViewMatrix();

			// Get the uniform locations
			GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
			GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
			GLint projLoc = glGetUniformLocation(ourShader.Program, "projection");

			// Pass the matrices to the shader
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

			// Fix angles
			int limit = arm->getParts()->size();
			for (int i = 0; i < movIndex; i++)
			{
				ArmMovement* movement = movements->at(i);

				for (int j = 0; j < movement->endPoint; j++)
				{
					Mesh* mesh = meshList.at(j);

					mesh->bind();

					glm::mat4 model;
					model = glm::translate(model, movement->pointAngle);
					model = glm::rotate(model, movement->endAngle, glm::vec3(0.0f, 0.0f, 1.0f));
					model = glm::translate(model, movement->points.at(j));
					glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

					mesh->draw();
				}
			}

			// Movement angle
			ArmMovement* movement = movements->at(movIndex);
			float anglePrev = 0.0f;
			for (int j = movement->startPoint; j < movement->endPoint; j++)
			{
				Mesh* mesh = meshList.at(j);

				mesh->bind();

				glm::mat4 model;
				model = glm::translate(model, movement->pointAngle);
				float angle = (MINIMUM_VALUE(currentTime, endTime) - startTime) / duration * movement->angled + movement->startAngle;
				model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
				model = glm::translate(model, movement->points.at(j));
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

				mesh->draw();

				anglePrev = angle;
			}

			glBindVertexArray(0);

			// Swap the buffers
			glfwSwapBuffers(window);
		}

		artPicture->finishMesh();
		glfwTerminate();

		return EXIT_SUCCESS;
	}
	catch (DisplayException e)
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		movements->at(movIndex)->endPoint = movements->at(movIndex + 1)->startPoint;
		movIndex++;
		duration = movements->at(movIndex)->angled / (2 * M_PI) * 10;
		startTime = currentTime;
		endTime = startTime + duration;
		cout << "SPACE \n";
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			camera->keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			camera->keys[key] = false;
		}
	}
}

void mouseCallback(GLFWwindow *window, double xPos, double yPos)
{
	if (camera->firstMouse)
	{
		camera->lastX = xPos;
		camera->lastY = yPos;
		camera->firstMouse = false;
	}

	GLfloat xOffset = xPos - camera->lastX;
	GLfloat yOffset = camera->lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	camera->lastX = xPos;
	camera->lastY = yPos;

	camera->ProcessMouseMovement(xOffset, yOffset);
}


void scrollCallback(GLFWwindow *window, double xOffset, double yOffset)
{
	camera->ProcessMouseScroll(yOffset);
}