//------------------------------------------------------------------------------
//
// Author: Hxx
//   Data: 18/8/2022
//
// Feature:
// -[x] 写一个新的 fragment shader，输出黄色图形
// -[x] 初始化两个 shader program，第二个用新的 fragment shader
// -[x] 绘制两个三角形，让第二个输出为黄色（用 glDrawArray 划分两个图形，避免新的 VAO 和 VBO）
//
//------------------------------------------------------------------------------

#ifndef LEARNGL_PRACTICE_HELLOTRIANGLE_3
#define LEARNGL_PRACTICE_HELLOTRIANGLE_3

#include "../../../Template/BasicVBO.hpp"

namespace learngl_practice {

using namespace std;

class DuoShaderProgram final : public gl_template::BasicVBO
{
public:
	static const char* YELLOW_FRAGMENT_SHADER;

private:
	unsigned int __shader_program_2;

protected:
	void _InitShaderProgram() override;
	void _UpdateRender() override;
};

} // namespace learngl_practice

#endif