#include "FragmentInterpolation.hpp"

namespace learngl_ch2 {

float FragmentInterpolation::VERTICES[18] = {
	// 位置             // 颜色
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // 右下
	-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // 左下
	0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // 顶部
};

const char* FragmentInterpolation::VERTEX_SHADER =
    "#version 330 core\n"
    "layout (location = 0) in vec3 a_pos;   // 位置变量的属性位置值为 0\n"
    "layout (location = 1) in vec3 a_color; // 颜色变量的属性位置值为 1\n"
    "out vec3 our_color; // 向片段着色器输出一个颜色\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(a_pos, 1.0);\n"
    "    our_color = a_color; // 将our_color设置为我们从顶点数据那里得到的输入颜色\n"
    "}\0";

const char* FragmentInterpolation::FRAGMENT_SHADER =
    "#version 330 core\n"
    "out vec4 frag_color;\n"
    "in vec3 our_color;\n"
    "void main()\n"
    "{\n"
    "    frag_color = vec4(our_color, 1.0);\n"
    "}\0";

void FragmentInterpolation::_InitShaderProgram()
{
	unsigned int vertex_shader   = _CreateVertexShader(VERTEX_SHADER);
	unsigned int fragment_shader = _CreateFragmentShader(FRAGMENT_SHADER);

	_shader_program = _CreateShaderProgram({ vertex_shader, fragment_shader });

	glDeleteShader(vertex_shader);   // 删除着色器
	glDeleteShader(fragment_shader); // 删除着色器
}

void FragmentInterpolation::_InitBufferData()
{
	// NOTE Bind 属于拷贝数据的一部分（而不是初始化）
	glBindVertexArray(_VAO); // 这里要先绑定 VAO
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW); // CRITICAL 绑定顶点数据

	// 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void FragmentInterpolation::_UpdateRender()
{
	glUseProgram(_shader_program);
	glBindVertexArray(_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

} // namespace learngl_ch2