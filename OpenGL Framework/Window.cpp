#include "Window.h"

Window::Window() {
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		pause();
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//Window creation
	theWindow = glfwCreateWindow(800, 800, "Left and Right to move, Space to calculate path", nullptr, nullptr); // Windowed, can do Fullscreen here
	//GLFWwindow* window = glfwCreateWindow(1920, 1080, "OpenGL", glfwGetPrimaryMonitor(), nullptr); // Fullscreen

	if (theWindow == NULL){
		glfwTerminate();
		fprintf(stderr, "Failed to open GLFW window. Your GPU is probably not compatible with this version of OpenGL.\n");
		pause();
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(theWindow);

	//GLEW Init
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		glfwDestroyWindow(theWindow);
		glfwTerminate();
		fprintf(stderr, "Failed to initialize GLEW\n");
		pause();
		exit(EXIT_FAILURE);
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(theWindow, GLFW_STICKY_KEYS, GL_TRUE);

	// Blue background
	glClearColor(0.3f, 0.3f, 0.6f, 0.0f);

	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

}


Window::~Window() {
	glfwDestroyWindow(theWindow);
	glfwTerminate();
}

glm::vec2 Window::getCursorPos() {
	double x, y;
	glfwGetCursorPos(theWindow, &x, &y);
	return glm::vec2(x, y);
}

void Window::centerCursor() {
	glfwSetCursorPos(theWindow, 400.0,300.0);
}

bool Window::isMousePressed() {
	return glfwGetMouseButton(theWindow, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS;
}

bool Window::isKeyPressed(GLint key) {
	return glfwGetKey(theWindow, key) == GLFW_PRESS;
}

bool Window::isKeyReleased(GLint key) {
	return glfwGetKey(theWindow, key) == GLFW_RELEASE;
}

void Window::pause() {
	std::cout << std::endl << "Press Enter to continue...";
	getchar();
}