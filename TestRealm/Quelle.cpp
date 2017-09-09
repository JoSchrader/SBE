#define GLEW_STATIC
#define GLEW_NO_GLU

#include "..\GLEW\src\glew.h"
#include "..\GLFW\src\glfw3.h"

void main()
{
	GLFWwindow* window;
	glfwInit();
	window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
	glfwDestroyWindow(window);
	glfwTerminate();
}