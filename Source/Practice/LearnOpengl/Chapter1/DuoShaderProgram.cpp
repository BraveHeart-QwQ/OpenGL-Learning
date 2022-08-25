#include "DuoShaderProgram.hpp"
#include <iostream>

namespace learngl_practice {

const char* DuoShaderProgram::YELLOW_FRAGMENT_SHADER = "#version 330 core\nout vec4 FragColor;\nvoid main()\n{\nFragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n}\0"; // 换成黄色

void DuoShaderProgram::_InitShaderProgram()
{
	unsigned int vertex_shader     = _CreateVertexShader(_vertex_shader_source.c_str());
	unsigned int fragment_shader_1 = _CreateFragmentShader(_fragment_shader_source.c_str());
	unsigned int fragment_shader_2 = _CreateFragmentShader(YELLOW_FRAGMENT_SHADER);

	_shader_program    = _CreateShaderProgram({ vertex_shader, fragment_shader_1 });
	__shader_program_2 = _CreateShaderProgram({ vertex_shader, fragment_shader_2 });

	glDeleteShader(vertex_shader);     // 删除着色器
	glDeleteShader(fragment_shader_1); // 删除着色器
	glDeleteShader(fragment_shader_2); // 删除着色器
}

void DuoShaderProgram::_UpdateRender()
{
	glUseProgram(_shader_program);
	glDrawArrays(GL_TRIANGLES, 0, 3); // 画第一个三角形

	glUseProgram(__shader_program_2);
	glDrawArrays(GL_TRIANGLES, 3, 3); // 画第二个三角形
}

} // namespace learngl_practice