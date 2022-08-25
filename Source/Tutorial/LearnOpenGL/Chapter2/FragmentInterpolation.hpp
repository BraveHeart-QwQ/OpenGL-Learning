//------------------------------------------------------------------------------
//
// Author: Hxx
//   Date: 24/8/22
//
// Description:
// 绘制一个“三角形调色板”，使用默认插值（Fragment Interpolation）算法、添加更多顶点属性
//
//------------------------------------------------------------------------------

#ifndef GLlEARNING_CH2_FRAGMENTINTERPOLATION
#define GLlEARNING_CH2_FRAGMENTINTERPOLATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../../Template/BasicVBO.hpp"

namespace learngl_ch2 {

class FragmentInterpolation final : public gl_template::BasicVBO
{
public:
	static float       VERTICES[18];
	static const char* VERTEX_SHADER;
	static const char* FRAGMENT_SHADER;

protected:
	virtual void _InitShaderProgram() override;
	virtual void _InitBufferData() override;
	virtual void _UpdateRender() override;
};

} // namespace learngl_ch2


#endif