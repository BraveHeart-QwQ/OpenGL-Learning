#include "Practice.hpp"
#include <iostream>

namespace learngl_practice {

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

} // namespace learngl_practice