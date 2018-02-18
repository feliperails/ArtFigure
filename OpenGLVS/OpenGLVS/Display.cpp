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

	glfwGetFramebufferSize(this->window, &this->screenWidth, &this->screenHeight);
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