#include "DiscolourTriangle.hpp"

namespace learngl_ch2 {

const char* DiscolourTriangle::VERTEX_SHADER =
    "#version 330 core\n"
    "layout (location = 0) in vec3 a_pos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(a_pos, 1.0);\n"
    "}\0";

const char* DiscolourTriangle::FRAGMENT_SHADER =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 our_color;\n"
    "void main()\n"
    "{\n"
    "   FragColor = our_color;\n"
    "}\n\0";

void DiscolourTriangle::_InitShaderProgram()
{
	unsigned int vertex_shader   = _CreateVertexShader(VERTEX_SHADER);
	unsigned int fragment_shader = _CreateFragmentShader(FRAGMENT_SHADER);

	_shader_program = _CreateShaderProgram({ vertex_shader, fragment_shader });

	glDeleteShader(vertex_shader);   // 删除着色器
	glDeleteShader(fragment_shader); // 删除着色器
}

void DiscolourTriangle::_UpdateRender()
{
	// Use program First!!!
	glUseProgram(_shader_program);

	// Update uniform variable in shader
	float time_val              = glfwGetTime();
	float green_val             = sin(time_val) / 2.0f + 0.5f;
	int   vertex_color_location = glGetUniformLocation(_shader_program, "our_color");
	glUniform4f(vertex_color_location, 0.0f, green_val, 0.0f, 1.0f);

	// Draw Triangle
	glBindVertexArray(_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

} // namespace learngl_ch2