#include "DrawMoreTriangle.hpp"

namespace learngl_practice {

float DrawMoreTriangle::VERTICES[18] = {
	-0.5, -0.5, 0,
	0, -0.5, 0,
	0, 0.5, 0,
	0.5, -0.5, 0,
	0, -0.5, 0,
	0, 0.5, 0
};

void DrawMoreTriangle::_InitBufferData()
{
	glBindVertexArray(_VAO); // 这里要先绑定 VAO
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void DrawMoreTriangle::_UpdateRender()
{
	glUseProgram(_shader_program);
	glBindVertexArray(_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6); // CRITICAL 这里最后一个参数要设为 6，因为我们有 6 个顶点
}

} // namespace learngl_practice