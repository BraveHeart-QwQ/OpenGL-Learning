//------------------------------------------------------------------------------
//
// Author: Hxx
//   Data: 14/8/2022
//
// Feature:
// -[ ] // TODO
// -[ ]
// -[ ]
//
//------------------------------------------------------------------------------

#ifndef TEMPLATE_BASIC1
#define TEMPLATE_BASIC1

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <initializer_list>
#include <string>

namespace gl_template {

class Basic
{
	/*-------------------- Protected Variable --------------------*/
	/*          [ User Init Config ]          */
protected:
	int           _window_width;
	int           _window_height;
	float*        _vertices;
	int           _vertices_size;
	unsigned int* _indices;
	int           _indices_size;
	std::string   _vertex_shader_source;
	std::string   _fragment_shader_source;

	/*          [ Class Data ]          */
protected:
	unsigned int _VBO;
	unsigned int _IBO;
	unsigned int _VAO;
	unsigned int _shader_program;
	GLFWwindow*  _window;

	/*-------------------- Public Method --------------------*/
	/*          [ Copy Control ]          */
public:
	Basic();

	Basic(int window_width,
	      int window_height);

	Basic(std::string vertex_shader_source,
	      std::string fragment_shader_source);

	Basic(float        vertices[],
	      int          vertices_size,
	      unsigned int indices[],
	      int          indices_size);

	Basic(int          window_width,
	      int          window_height,
	      float        vertices[],
	      int          vertices_size,
	      unsigned int indices[],
	      int          indices_size);

	Basic(int         window_width,
	      int         window_height,
	      std::string vertex_shader_source,
	      std::string fragment_shader_source);

	Basic(int          window_width,
	      int          window_height,
	      float        vertices[],
	      int          vertices_size,
	      unsigned int indices[],
	      int          indices_size,
	      std::string  vertex_shader_source,
	      std::string  fragment_shader_source);

	/*          [ User Interface ]          */
public:
	int         RealMain(int argc, const char* argv[]);
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void UpdateProcessInput(GLFWwindow* window);

	/*-------------------- Protected Method --------------------*/
	/*          [ RealMain Template Method ]          */
protected:
	virtual void         _InitGLFW();
	virtual GLFWwindow*  _InitWindow(const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	virtual bool         _InitGlad();
	virtual void         _InitViewPort();
	virtual unsigned int _InitShaderProgram();
	virtual void         _InitBuffer();
	virtual void         _InitBufferData();
	virtual void         _InitRenderConfig();
	virtual void         _RenderLoop();
	virtual void         _Terminal();

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