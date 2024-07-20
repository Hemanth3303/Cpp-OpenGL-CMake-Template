#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#ifdef _MSC_VER
#pragma warning(disable: 5105) 
#endif // _MSC_VER

void handleInputs(GLFWwindow* window);
void framebufferResizeCallback(GLFWwindow* window, int width, int height);

int main() {
#if defined(APP_DEBUG)
	std::cout << "Debug Build\n";
#elif defined(APP_RELEASE)
	std::cout << "Release Build\n";
#elif defined(APP_DIST)
	std::cout << "Distribution Build\n";
#else

#endif 
	int width = 640, height = 480;
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Hello OpenGL", NULL, NULL);

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Error: Failed to initialize glad\n";
		glfwTerminate();
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	GLfloat vertices[] = {
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // right
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // left
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // top
	};

	const char* vsSource = "#version 460 core\n"
		"layout (location=0) in vec3 aPos;\n"
		"layout (location=1) in vec3 aColor;\n"
		"out vec4 color;\n"
		"void main() {\n"
		"	gl_Position=vec4(aPos, 1.0);\n"
		"	color=vec4(aColor, 1.0f);\n"
		"}\0";

	const char* fsSource = "#version 460 core\n"
		"out vec4 FragColor;\n"
		"in vec4 color;\n"
		"void main() {\n"
		"	FragColor=color;\n"
		"}\0";

	int success;
	char infoLog[1024];

	GLuint vs, fs, shader;

	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vsSource, NULL);
	glCompileShader(vs);

	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vs, 1024, NULL, infoLog);
		std::cout << "Error: vertex shader compile: error\n" << infoLog << "\n";
	}

	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fsSource, NULL);
	glCompileShader(fs);

	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fs, 1024, NULL, infoLog);
		std::cout << "Error: fragment shader compile: error\n" << infoLog << "\n";
	}

	shader = glCreateProgram();
	glAttachShader(shader, vs);
	glAttachShader(shader, fs);
	glLinkProgram(shader);

	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader, 1024, NULL, infoLog);
		std::cout << "Error: Program failed to compile: error\n" << infoLog << "\n";
	}

	glDeleteShader(vs);
	glDeleteShader(fs);

	GLuint vbo, vao;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window)) {
		// update
		handleInputs(window);
		glfwPollEvents();

		//render
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shader);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteProgram(shader);

	glfwTerminate();

	return 0;
}

void handleInputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}