//------------------------------------------------------------------------------
//
// Author: Hxx
//   Date: 18/8/2022
//
// Feature:
// -[x] 创建两个 VAO 和两个 VBO，然后分别用它们绘制同一个数据
//
//------------------------------------------------------------------------------
#ifndef LEARNGL_PRACTICE_HELLOTRIANGLE_2
#define LEARNGL_PRACTICE_HELLOTRIANGLE_2

#include "../../../Template/BasicVBO.hpp"

namespace learngl_practice {

using namespace std;

class DrawTwoTriangleInDiffVAOVBO final : public gl_template::BasicVBO
{
public:
	static float VERTICES[18];

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