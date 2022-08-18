#include "Practice.hpp"
#include <iostream>

namespace learngl_practice {

void DrawTwoTriangleInDiffVAOVBO::_InitBuffer()
{
	glGenVertexArrays(2, __vaos); // CRITICAL 同时生成多个 vao 和 vbo，注意这里不需要用`&`，因为数组可以自动转为指针
	glGenBuffers(2, __vbos);
}

void DrawTwoTriangleInDiffVAOVBO::_InitBufferData()
{
	/* 绑定第一套 vao、vbo 的数据 */
	glBindVertexArray(__vaos[0]);
	glBindBuffer(GL_ARRAY_BUFFER, __vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, _vertices_size, _vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//glBindVertexArray(0); // 这行代码可以取消 vao 的绑定，但没必要

	/* 绑定第二套 vao、vbo 的数据 */
	glBindVertexArray(__vaos[1]);
	glBindBuffer(GL_ARRAY_BUFFER, __vbos[1]);
	glBufferData(GL_ARRAY_BUFFER, _vertices_size, _vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void DrawTwoTriangleInDiffVAOVBO::_UpdateRender()
{
	glUseProgram(_shader_program);

	/* 用第一套 vao、vbo 画同一个三角形数据 */
	glBindVertexArray(__vaos[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	/* 用第二套 vao、vbo 画同一个三角形数据 */
	glBindVertexArray(__vaos[1]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void DrawTwoTriangleInDiffVAOVBO::_InitRenderConfig()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 线框模式
}

} // namespace learngl_practice