#include "shader.h"
#include <cassert>
#include <fstream>
#include <iostream>

std::string read_file(const std::string &&file_path) {
	std::ifstream file{file_path};
	assert(file.is_open());
	std::string str;
	file.seekg(0, std::ios::end);
	str.reserve(file.tellg());
	file.seekg(0, std::ios::beg);
	str.assign({std::istreambuf_iterator<char>{file},
		    std::istreambuf_iterator<char>{}});
	return str;
}

GLuint compile_shader(const std::string &&shader_path, GLenum shader_type) {
	std::string vertex_shader_code = read_file(std::move(shader_path));
	const char *cstr_vertex_shader_code = vertex_shader_code.c_str();
	GLuint vertex_shader = glCreateShader(shader_type);
	glShaderSource(vertex_shader, 1, &cstr_vertex_shader_code, nullptr);
	glCompileShader(vertex_shader);

	GLint success;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	char info_log[512];
	if (!success) {
		glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
		std::cerr << "Error compiling shader " << shader_path << ": "
			  << info_log << '\n';
	}
	return vertex_shader;
}

Shader::Shader(const std::string &&vertex_shader_path,
	       const std::string &&fragment_shader_path)
	: program(glCreateProgram()) {
	GLuint vertex_shader =
		compile_shader(std::move(vertex_shader_path), GL_VERTEX_SHADER);
	GLuint fragment_shader = compile_shader(std::move(fragment_shader_path),
						GL_FRAGMENT_SHADER);

	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	// @TODO: add error checking for the link

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

void Shader::bind() { glUseProgram(program); }

void Shader::unbind() { glUseProgram(0); }

Shader::~Shader() { glDeleteProgram(program); }