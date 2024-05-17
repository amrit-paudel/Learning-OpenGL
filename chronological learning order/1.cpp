
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main() {

	glfwInit();

	// we are using open gl 3.3
	// by this we are telling the glfw that we are 
	// using 3.3 version of open gl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// telling glfw that we are using CORE profile
	// so that we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	
	GLFWwindow* window = glfwCreateWindow(800, 800, "first window", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// we make our created window as the current context
	glfwMakeContextCurrent(window);

	// we load the glad 
	gladLoadGL();


	// specify the size of rendering window inside the window
	glViewport(0, 0, 800, 800);

	// specify the color of background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	// clean the back buffer and assign new color to it
	glClear(GL_COLOR_BUFFER_BIT);

	// swap the back buffer with the front buffer
	glfwSwapBuffers(window);


    // our rendering loop
	while (!glfwWindowShouldClose(window)) {

		// takes care of all the mouse and keyboard events in the created window
		glfwPollEvents();
	}
	
	// a destructor to destroy the created window object
	glfwDestroyWindow(window);

	// to terminate the glfw after all the work is done
	glfwTerminate();

	return 0;
}