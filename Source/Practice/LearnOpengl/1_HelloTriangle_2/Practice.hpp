//------------------------------------------------------------------------------
//
// Author: Hxx
//   Data: 18/8/2022
//
// Feature:
// -[x] 创建两个 VAO 和两个 VBO，然后分别用它们绘制同一个数据
//
//------------------------------------------------------------------------------
#ifndef LEARNGL_PRACTICE_HELLOTRIANGLE_2
#define LEARNGL_PRACTICE_HELLOTRIANGLE_2

#include <array>
#include "../../../Template/1_Basic/Basic.hpp"

namespace learngl_practice {

using namespace std;

class DrawTwoTriangleInDiffVAOVBO final : public gl_template::Basic
{
private:
	unsigned int __vbos[2] = { 0, 0 };
	unsigned int __vaos[2] = { 0, 0 };

protected:
	void _InitBuffer() override;
	void _InitBufferData() override;
	void _UpdateRender() override;
	void _InitRenderConfig() override;
};

} // namespace learngl_practice

#endif