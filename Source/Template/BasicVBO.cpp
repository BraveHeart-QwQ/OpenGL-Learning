#include "BasicVBO.hpp"
#include <iostream>

namespace gl_template {

const char* BasicVBO::DEFAULT_VERTEX_SHADER   = "#version 330 core\nlayout (location = 0) in vec3 aPos;\nvoid main()\n{\ngl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n}\0";
const char* BasicVBO::DEFAULT_FRAGMENT_SHADER = "#version 330 core\nout vec4 FragColor;\nvoid main()\n{\nFragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n}\0";
float       BasicVBO::DEFAULT_VERTICES[18]    = {
    -0.75f, -0.2165f, 0.0f,
    -0.25f, -0.2165f, 0.0f,
    -0.5f, 0.2165f, 0.0f,
    0.25f, -0.2165f, 0.0f,
    0.75f, -0.2165f, 0.0f,
    0.5f, 0.2165f, 0.0f
};

BasicVBO::BasicVBO()
    : BasicVBO(600, 600) { }

BasicVBO::BasicVBO(int window_width,
                   int window_height)
    : BasicVBO(window_width,
               window_height,
               DEFAULT_VERTICES,
               sizeof(DEFAULT_VERTICES)) { }

BasicVBO::BasicVBO(const std::string& vertex_shader_source,
                   const std::string& fragment_shader_source)
    : BasicVBO(600,
               600,
               vertex_shader_source,
               fragment_shader_source) { }

BasicVBO::BasicVBO(float vertices[], unsigned int vertices_size)
    : BasicVBO(600,
               600,
               vertices,
               vertices_size) { }

BasicVBO::BasicVBO(int          window_width,
                   int          window_height,
                   float        vertices[],
                   unsigned int vertices_size)
    : BasicVBO(window_width,
               window_height,
               vertices,
               vertices_size,
               DEFAULT_VERTEX_SHADER,
               DEFAULT_FRAGMENT_SHADER) { }

BasicVBO::BasicVBO(int                window_width,
                   int                window_height,
                   const std::string& vertex_shader_source,
                   const std::string& fragment_shader_source)
    : BasicVBO(window_width,
               window_height,
               DEFAULT_VERTICES,
               sizeof(DEFAULT_VERTICES),
               vertex_shader_source,
               fragment_shader_source) { }

BasicVBO::BasicVBO(int                window_width,
                   int                window_height,
                   float              vertices[],
                   unsigned int       vertices_size,
                   const std::string& vertex_shader_source,
                   const std::string& fragment_shader_source)
    : _window_width(window_width),
      _window_height(window_height),
      _vertices(vertices),
      _vertices_size(vertices_size),
      _vertex_shader_source(vertex_shader_source),
      _fragment_shader_source(fragment_shader_source) { }

int BasicVBO::RealMain(int argc, const char* argv[])
{
	_InitGLFW();

	_InitWindow("LearnOpenGL", NULL, NULL);

	if (_InitGlad() == false) return -1; // ????????????????????? _InitWindow ??????

	_InitViewPort();

	_InitShaderProgram();

	_InitBuffer();

	_InitBufferData();

	_InitRenderConfig();

	_RenderLoop();

	_Terminal();

	return 0;
}

void BasicVBO::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void BasicVBO::UpdateProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true); // ???????????? ESC??????????????????
}

void BasicVBO::_InitGLFW()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // ?????? OpenGL ??????
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // ?????? OpenGL ??????
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

bool BasicVBO::_InitGlad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { // ?????? GLFW ?????????????????? GLAD
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return false;
	}

	return true;
}

void BasicVBO::_InitWindow(const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
	_window = glfwCreateWindow(_window_width, _window_height, title, monitor, share);
	if (_window == NULL) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(_window);
}

void BasicVBO::_InitViewPort()
{
	glViewport(0, 0, _window_width, _window_height);
	glfwSetFramebufferSizeCallback(_window, BasicVBO::FramebufferSizeCallback);
}

unsigned int BasicVBO::_CreateVertexShader(const char* shader_source)
{
	/* ?????? Vertex Shader */
	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER); // ???????????? Vertex Shader
	glShaderSource(vertex_shader, 1, &shader_source, NULL);        // ??? Shader ?????? GLSL ??????
	glCompileShader(vertex_shader);                                // ?????? GLSL ??????

	/* ?????? Vertex Shader ???????????????????????????????????? */
	int  success;
	char info_log[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
		          << info_log << std::endl;
	}

	return vertex_shader;
}

unsigned int BasicVBO::_CreateFragmentShader(const char* shader_source)
{
	/* ?????? Fragment Shader */
	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &shader_source, NULL);
	glCompileShader(fragment_shader);

	/* ?????? Fragment Shader ???????????????????????????????????? */
	int  success;
	char info_log[512];
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
		          << info_log << std::endl;
	}

	return fragment_shader;
}

unsigned int BasicVBO::_CreateShaderProgram(std::initializer_list<unsigned int> shader_li)
{
	unsigned int shader_program = glCreateProgram();
	std::for_each(shader_li.begin(), shader_li.end(), [shader_program](unsigned int i) {
		glAttachShader(shader_program, i);
	});
	glLinkProgram(shader_program);

	int  success;
	char info_log[512];
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program, 512, NULL, info_log);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
		          << info_log << std::endl;
	}

	return shader_program;
}

void BasicVBO::_InitShaderProgram()
{
	unsigned int vertex_shader   = _CreateVertexShader(_vertex_shader_source.c_str());
	unsigned int fragment_shader = _CreateFragmentShader(_fragment_shader_source.c_str());

	_shader_program = _CreateShaderProgram({ vertex_shader, fragment_shader });

	glDeleteShader(vertex_shader);   // ???????????????
	glDeleteShader(fragment_shader); // ???????????????
}

void BasicVBO::_InitBuffer()
{
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
}

void BasicVBO::_InitBufferData()
{
	// NOTE Bind ??????????????????????????????????????????????????????
	glBindVertexArray(_VAO); // ?????????????????? VAO
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);

	glBufferData(GL_ARRAY_BUFFER, _vertices_size, _vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void BasicVBO::_InitRenderConfig()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // ????????????????????????
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // ????????????
}

void BasicVBO::_RenderLoop()
{
	while (!glfwWindowShouldClose(_window)) {
		_UpdateBeforeRender();
		_UpdateClear();
		_UpdateRender();
		_UpdateAfterRender();
	}
}

void BasicVBO::_UpdateBeforeRender()
{
	UpdateProcessInput(_window); // Handle Input
}

void BasicVBO::_UpdateClear()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // ?????????????????????????????????
	glClear(GL_COLOR_BUFFER_BIT);         // ??????????????????????????????
}

void BasicVBO::_UpdateRender()
{
	glUseProgram(_shader_program);
	glBindVertexArray(_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void BasicVBO::_UpdateAfterRender()
{
	glfwSwapBuffers(_window); // ????????????
	glfwPollEvents();         // ????????????
}

void BasicVBO::_Terminal()
{
	/* ?????????????????????????????? */
	//glDeleteVertexArrays(1, &_VAO);
	//glDeleteBuffers(1, &_VBO);
	//glDeleteProgram(_shader_program);

	glfwTerminate(); // ??????????????????????????????????????????
}

} // namespace gl_template