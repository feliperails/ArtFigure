#include "Display.h"

using namespace std;

Display::Display()
{

}

void Display::init(GLuint width, GLuint height, string title) {
	this->width = width;
	this->height = height;
	this->title = title;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	this->window = glfwCreateWindow(this->width, this->height, "Figuras Articuladas", nullptr, nullptr);

	if (nullptr == this->window)
	{
		throw new DisplayException();
	}

	glfwMakeContextCurrent(this->window);
	glfwSwapInterval(1);
	glfwGetFramebufferSize(this->window, &this->screenWidth, &this->screenHeight);
}

void Display::initGL() {
	if (GLEW_OK != glewInit())
	{
		throw new DisplayGLException;
	}

	/*
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	printf("Renderer: %s\n", renderer);
	printf("OpenGL (versao suportada) %s\n", version);
	*/

	// Define the viewport dimensions
	glViewport(0, 0, this->width, this->height);

	// Setup some OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

GLuint Display::getWidth() {
	return this->width;
}

GLuint Display::getHeight() {
	return this->height;
}

GLFWwindow* Display::getWindow() {
	return this->window;
}