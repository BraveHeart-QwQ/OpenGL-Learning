//------------------------------------------------------------------------------
//
// Author: Hxx
//   Data: 14/8/2022
//
// Description:
// 基于 VBO 的 OpenGL 图形绘制
//
//------------------------------------------------------------------------------

#ifndef TEMPLATE_BASIC_VBO
#define TEMPLATE_BASIC_VBO

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <initializer_list>
#include <string>

namespace gl_template {

// TODO 提供接口动态读写 User Init Data
class BasicVBO
{
	/*-------------------- Public Variable --------------------*/
public:
	static const char* DEFAULT_VERTEX_SHADER;
	static const char* DEFAULT_FRAGMENT_SHADER;
	static float       DEFAULT_VERTICES[18];

	/*-------------------- Protected Variable --------------------*/
protected:
	/*          [ User Init Data ]          */
	int          _window_width;
	int          _window_height;
	float*       _vertices;
	unsigned int _vertices_size;
	std::string  _vertex_shader_source;
	std::string  _fragment_shader_source;

	/*          [ Class Data ]          */
	unsigned int _VBO;
	unsigned int _VAO;
	unsigned int _shader_program;
	GLFWwindow*  _window;

	/*-------------------- Public Method --------------------*/
public:
	/*          [ Copy Control ]          */
	BasicVBO();
	BasicVBO(int window_width,
	         int window_height);
	BasicVBO(const std::string& vertex_shader_source,
	         const std::string& fragment_shader_source);
	BasicVBO(float        vertices[],
	         unsigned int vertices_size);
	BasicVBO(int          window_width,
	         int          window_height,
	         float        vertices[],
	         unsigned int vertices_size);
	BasicVBO(int                window_width,
	         int                window_height,
	         const std::string& vertex_shader_source,
	         const std::string& fragment_shader_source);
	BasicVBO(int                window_width,
	         int                window_height,
	         float              vertices[],
	         unsigned int       vertices_size,
	         const std::string& vertex_shader_source,
	         const std::string& fragment_shader_source);

	//~Basic(); // NOTE 本类没有使用 new 来获取资源，默认数据都存在栈上

	/*          [ User Interface ]          */
	virtual int RealMain(int argc, const char* argv[]);
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void UpdateProcessInput(GLFWwindow* window);

	/*-------------------- Protected Method --------------------*/
protected:
	/*          [ RealMain Template Method ]          */
	virtual void _InitGLFW();
	virtual void _InitWindow(const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	virtual bool _InitGlad();
	virtual void _InitViewPort();
	virtual void _InitShaderProgram();
	virtual void _InitBuffer();
	virtual void _InitBufferData();
	virtual void _InitRenderConfig();
	virtual void _RenderLoop();
	virtual void _Terminal();

	/*          [ _InitShaderProgram Template Method ]          */
	virtual unsigned int _CreateVertexShader(const char* shader_source);
	virtual unsigned int _CreateFragmentShader(const char* shader_source);
	virtual unsigned int _CreateShaderProgram(std::initializer_list<unsigned int> shader_li);

	/*          [ _RenderLoop Template Method ]          */
	virtual void _UpdateBeforeRender();
	virtual void _UpdateClear();
	virtual void _UpdateRender();
	virtual void _UpdateAfterRender();
};

} // namespace gl_template

#endif