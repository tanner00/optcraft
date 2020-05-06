#pragma once

#include <glad/glad.h>
#include <string_view>

class Shader {
    private:
	GLuint m_program;

    public:
	Shader(std::string_view vertex_shader_path,
	       std::string_view fragment_shader_path);
	~Shader();

	void set_uniform(std::string_view name, float value);

	void bind();
	void unbind();
};