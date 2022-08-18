//------------------------------------------------------------------------------
//
// Author: Hxx
//   Data: 18/8/2022
//
// Feature:
// -[ ] 写一个新的 fragment shader，输出黄色图形
// -[ ] 初始化两个 shader program，第二个用新的 fragment shader
// -[ ] 绘制两个三角形，让第二个输出为黄色
//
//------------------------------------------------------------------------------
#ifndef LEARNGL_PRACTICE_HELLOTRIANGLE_3
#define LEARNGL_PRACTICE_HELLOTRIANGLE_3

#include "../../../Template/1_Basic/Basic.hpp"

namespace learngl_practice {

using namespace std;

class DuoShaderProgram final : public gl_template::Basic
{
public:
	static const char* YELLOW_FRAGMENT_SHADER;

private:
	unsigned int __shader_program_2;

protected:
	void _InitShaderProgram() override;

	//void _InitBuffer() override;
	//void _InitBufferData() override;
	//void _UpdateRender() override;
	//void _InitRenderConfig() override;
};

} // namespace learngl_practice

#endif