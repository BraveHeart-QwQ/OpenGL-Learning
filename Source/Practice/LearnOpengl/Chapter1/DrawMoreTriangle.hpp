//------------------------------------------------------------------------------
//
// Author: Hxx
//   Data: 16/8/2022
//
// Description:
// 用 glDrawArrays() 绘制两个相邻的三角形
//
// Feature:
// -[x] 提供新的 vertices 数组
// -[x] 修改 _InitBufferData()，使用心得顶点数据
// -[x] 修改 _UpdateRender()，使用 glDrawArrays() 来绘制图形
//
//------------------------------------------------------------------------------
#ifndef LEARNGL_PRACTICE_HELLOTRIANGLE_1
#define LEARNGL_PRACTICE_HELLOTRIANGLE_1

#include "../../../Template/BasicVBO.hpp"

namespace learngl_practice {

class DrawMoreTriangle : public gl_template::BasicVBO
{
public:
	static float VERTICES[18];

protected:
	void _InitBufferData() override;
	void _UpdateRender() override;
};

} // namespace learngl_practice

#endif
