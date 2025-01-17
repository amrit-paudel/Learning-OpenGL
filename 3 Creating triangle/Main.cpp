

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

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

	
    GLfloat vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
	};


	
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

	// here we set up the vertex shader
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);


	// here we setup the fragment shader
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);


	// here we link both the shaders in to the shaderProgram object
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);


	


	// creating VBO to send the vertex data to GPU from CPU
	// also creating the VAO object
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// stroing our vertices in the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);







	// specify the color of background
	//glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	// clean the back buffer and assign new color to it
	//glClear(GL_COLOR_BUFFER_BIT);

	// swap the back buffer with the front buffer
	glfwSwapBuffers(window);


    // our rendering loop
	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);



		// takes care of all the mouse and keyboard events in the created window
		glfwPollEvents();
	}

	// deleting the VAO and VBO object we created at last
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// freeing the memory occupied by the shaders objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	
	// a destructor to destroy the created window object
	glfwDestroyWindow(window);

	// to terminate the glfw after all the work is done
	glfwTerminate();

	return 0;
}

