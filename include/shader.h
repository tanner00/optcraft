#include <glad/glad.h>
#include <string>

class Shader {
    private:
	GLuint program;

    public:
	Shader(const std::string &&vertex_shader_path,
	       const std::string &&fragment_shader_path);
	~Shader();

	void bind();
	void unbind();
};