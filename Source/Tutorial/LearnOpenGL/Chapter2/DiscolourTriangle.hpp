//------------------------------------------------------------------------------
//
// Author: Hxx
//
// Description:
// 绘制一个颜色渐变的三角形
//
//------------------------------------------------------------------------------

#ifndef GLLEARNING_CH2_DISCOLOURTRIANGLE
#define GLLEARNING_CH2_DISCOLOURTRIANGLE

#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../../Template/BasicVBO.hpp"

namespace learngl_ch2 {

class DiscolourTriangle final : public gl_template::BasicVBO
{
public:
	static const char* VERTEX_SHADER;
	static const char* FRAGMENT_SHADER;

protected:
	void _InitShaderProgram() override;
	void _UpdateRender() override;
};

} // namespace learngl_ch2

#endif