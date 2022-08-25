//------------------------------------------------------------------------------
//
// Author: Hxx
//   Data: 14/8/2022
//
// Description:
// 基于虚函数的模版方法模式，可以通过继承来替换 OpenGL 的一些抽象步骤的实现，这个类展示了
// 基础情况下的 OpenGL 使用步骤。
//
//------------------------------------------------------------------------------

#ifndef TEMPLATE_BASIC_IBO
#define TEMPLATE_BASIC_IBO

#include "BasicVBO.hpp"

namespace gl_template {

// TODO 提供接口动态读写 User Init Data
class BasicIBO : public BasicVBO
{
	/*-------------------- Public Variable --------------------*/
public:
	static unsigned int DEFAULT_INDICES[6];

	/*-------------------- Protected Variable --------------------*/
protected:
	/*          [ User Init Data ]          */
	unsigned int* _indices;
	int           _indices_size;

	/*          [ Class Data ]          */
	unsigned int _IBO;

	/*-------------------- Public Method --------------------*/
public:
	/*          [ Copy Control ]          */
	BasicIBO();
	BasicIBO(int window_width,
	         int window_height);
	BasicIBO(const std::string& vertex_shader_source,
	         const std::string& fragment_shader_source);
	BasicIBO(float        vertices[],
	         unsigned int vertices_size,
	         unsigned int indices[],
	         unsigned int indices_size);
	BasicIBO(int          window_width,
	         int          window_height,
	         float        vertices[],
	         unsigned int vertices_size,
	         unsigned int indices[],
	         unsigned int indices_size);
	BasicIBO(int                window_width,
	         int                window_height,
	         const std::string& vertex_shader_source,
	         const std::string& fragment_shader_source);
	BasicIBO(int                window_width,
	         int                window_height,
	         float              vertices[],
	         unsigned int       vertices_size,
	         unsigned int       indices[],
	         unsigned int       indices_size,
	         const std::string& vertex_shader_source,
	         const std::string& fragment_shader_source);

	//~Basic(); // NOTE 本类没有使用 new 来获取资源，默认数据都存在栈上

	/*-------------------- Protected Method --------------------*/
protected:
	virtual void _InitBuffer() override;
	virtual void _InitBufferData() override;
	virtual void _UpdateRender() override;
};

} // namespace gl_template

#endif