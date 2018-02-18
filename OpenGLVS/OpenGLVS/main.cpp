// Std. Includes
#include <string>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

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

// Properties

GLfloat lastFrame = 0.0f;

Camera* camera;

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void mouseCallback(GLFWwindow *window, double xPos, double yPos);
void scrollCallback(GLFWwindow *window, double xOffset, double yOffset);

// The MAIN function, from here we start our application and run our Game loop
int main( )
{
	try
	{
		Display* display = new Display();

		display->init(800, 600, "Figuras Articuladas");
		GLFWwindow* window = display->getWindow();

		camera = new Camera(display);

		// Set the required callback functions
		glfwSetKeyCallback(display->getWindow(), keyCallback);
		glfwSetCursorPosCallback(display->getWindow(), mouseCallback);
		glfwSetScrollCallback(display->getWindow(), scrollCallback);

		// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
		glewExperimental = GL_TRUE;
		// Initialize GLEW to setup the OpenGL Function pointers
		if (GLEW_OK != glewInit())
		{
			std::cout << "Failed to initialize GLEW" << std::endl;
			return EXIT_FAILURE;
		}

		const GLubyte* renderer = glGetString(GL_RENDERER);
		const GLubyte* version = glGetString(GL_VERSION);
		printf("Renderer: %s\n", renderer);
		printf("OpenGL (versao suportada) %s\n", version);

		// Define the viewport dimensions
		glViewport(0, 0, display->getWidth(), display->getHeight());

		// Setup some OpenGL options
		glEnable(GL_DEPTH_TEST);

		// enable alpha support
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Setup and compile our shaders
		ShaderTest ourShader("res/shaders/core.vs", "res/shaders/core.frag");

		// Set up our vertex data (and buffer(s)) and attribute pointers
		GLfloat vertices[] =
		{
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			1.0f, -0.5f, -0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			/*
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
			*/
		};

		glm::vec3 cubePositions[] =
		{
			glm::vec3(0.0f, 0.0f, 0.0f)
			, glm::vec3( 2.0f, 5.0f, -15.0f )
			, glm::vec3( -1.5f, -2.2f, -2.5f )
			, glm::vec3( -3.8f, -2.0f, -12.3f )
			, glm::vec3( 2.4f, -0.4f, -3.5f )
			, glm::vec3( -1.7f, 3.0f, -7.5f )
			, glm::vec3( 1.3f, -2.0f, -2.5f )
			, glm::vec3( 1.5f, 2.0f, -2.5f )
			, glm::vec3( 1.5f, 0.2f, -1.5f )
			, glm::vec3( -1.3f, 1.0f, -1.5f )
		};

		int cubePositionsLength = 1;

		GLuint VBO, VAO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		// Bind our Vertex Array Object first, then bind and set our buffers and pointers.
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)0);
		glEnableVertexAttribArray(0);
		// TexCoord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0); // Unbind VAO

		// Load and create a texture
		GLuint texture;
		// --== TEXTURE == --
		glGenTextures( 1, &texture );
		glBindTexture( GL_TEXTURE_2D, texture ); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
		// Set our texture parameters
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		// Set texture filtering
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		// Load, create texture and generate mipmaps
		int width, height;
		unsigned char *image = SOIL_load_image( "res/images/image1.jpg", &width, &height, 0, SOIL_LOAD_RGB );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image );
		glGenerateMipmap( GL_TEXTURE_2D );
		SOIL_free_image_data( image );
		glBindTexture( GL_TEXTURE_2D, 0 ); // Unbind texture when done, so we won't accidentily mess up our texture.

		// Game loop
		while (!glfwWindowShouldClose(window))
		{
			// Set frame time
			GLfloat currentFrame = glfwGetTime();
			lastFrame = currentFrame;

			// Check and call events
			glfwPollEvents();
			camera->DoMovement(currentFrame - lastFrame);

			// Clear the colorbuffer
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Draw our first triangle
			ourShader.Use();

			// Bind Textures using texture units
			glActiveTexture( GL_TEXTURE0 );
			glBindTexture( GL_TEXTURE_2D, texture );
			glUniform1i( glGetUniformLocation( ourShader.Program, "ourTexture1" ), 0 );

			glm::mat4 projection;
			projection = glm::perspective(camera->GetZoom(), (GLfloat) display->screenWidth / (GLfloat) display->screenHeight, 0.1f, 1000.0f);

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

			glBindVertexArray(VAO);

			for (GLuint i = 0; i < cubePositionsLength; i++)
			{
				// Calculate the model matrix for each object and pass it to shader before drawing
				glm::mat4 model;
				model = glm::translate(model, cubePositions[i]);
				// GLfloat angle = 20.0f * i;
				// model = glm::rotate(model, angle, glm::vec3( 1.0f, 0.3f, 0.5f ) );
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

				glDrawArrays(GL_TRIANGLES, 0, 36);
			}

			glBindVertexArray(0);

			// Swap the buffers
			glfwSwapBuffers(window);
		}

		// Properly de-allocate all resources once they've outlived their purpose
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
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