#include <glad/glad.h>

#include "shader.h"
#include <GLFW/glfw3.h>
#include <cassert>
#include <iostream>

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 640;

int main() {

	assert(glfwInit());

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
					      "Optcraft", nullptr, nullptr);
	assert(window);
	glfwMakeContextCurrent(window);

	assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	GLfloat vertices[] = {
		-0.3f, 0.6f, 0.0f, 0.6f, 0.7f, 0.0f, 0.3f, 0.1f, 0.0f,
	};

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
		     GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
			      nullptr);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	Shader shader{"src/shaders/vertex.glsl", "src/shaders/fragment.glsl"};

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.bind();

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		shader.unbind();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}