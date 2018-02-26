#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <exception>

using namespace std;

class DisplayException : public exception
{
	virtual const char* what() const throw()
	{
		return "Failed to create GLFW window";
	}
};

class DisplayGLException : public exception
{
	virtual const char* what() const throw()
	{
		return "Failed to initialize GLEW";
	}
};

class Display {
public:
	int screenWidth;
	int screenHeight;

	Display();
	void init(GLuint width, GLuint height, string title);
	void initGL();
	GLuint getWidth();
	GLuint getHeight();
	GLFWwindow* getWindow();

private:
	GLuint width;
	GLuint height;
	string title;

	GLFWwindow* window;
};