#include "shader.h"
#include <cassert>
#include <fstream>
#include <iostream>

std::string read_text_file(std::string_view file_path) {
	std::ifstream file{file_path.data()};
	assert(file.is_open());
	std::string str;
	file.seekg(0, std::ios::end);
	str.reserve(file.tellg());
	file.seekg(0, std::ios::beg);
	str.assign({std::istreambuf_iterator<char>{file},
		    std::istreambuf_iterator<char>{}});
	return str;
}

GLuint compile_shader(std::string_view shader_path, GLenum shader_type) {
	std::string vertex_shader_code = read_text_file(shader_path);
	GLuint vertex_shader = glCreateShader(shader_type);
	const char *cstr_vertex_shader_code = vertex_shader_code.c_str();
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

Shader::Shader(std::string_view vertex_shader_path,
	       std::string_view fragment_shader_path)
	: m_program(glCreateProgram()) {

	GLuint vertex_shader =
		compile_shader(vertex_shader_path, GL_VERTEX_SHADER);
	GLuint fragment_shader =
		compile_shader(fragment_shader_path, GL_FRAGMENT_SHADER);

	glAttachShader(m_program, vertex_shader);
	glAttachShader(m_program, fragment_shader);
	glLinkProgram(m_program);

	char info_log[512];
	GLint success;
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_program, 512, NULL, info_log);
		std::cerr << "Error linking shader (" << vertex_shader_path
			  << ", " << fragment_shader_path << "): " << info_log
			  << '\n';
	}

	glDetachShader(m_program, vertex_shader);
	glDeleteShader(vertex_shader);
	glDetachShader(m_program, fragment_shader);
	glDeleteShader(fragment_shader);
}

void Shader::set_uniform(std::string_view name, float value) {
	glUniform1f(glGetUniformLocation(m_program, name.data()), value);
}

void Shader::bind() { glUseProgram(m_program); }

void Shader::unbind() { glUseProgram(0); }

Shader::~Shader() { glDeleteProgram(m_program); }