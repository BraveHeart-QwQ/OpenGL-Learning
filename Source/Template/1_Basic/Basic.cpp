#include "Basic.hpp"
#include <iostream>

namespace gl_template {

const char* Basic::DEFAULT_VERTEX_SHADER   = "#version 330 core\nlayout (location = 0) in vec3 aPos;\nvoid main()\n{\ngl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n}\0";
const char* Basic::DEFAULT_FRAGMENT_SHADER = "#version 330 core\nout vec4 FragColor;\nvoid main()\n{\nFragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n}\0";
float       Basic::DEFAULT_VERTICES[18]    = {
    -0.75f, -0.5f, 0.0f,
    -0.25f, -0.5f, 0.0f,
    -0.25f, 0.5f, 0.0f,
    0.25f, -0.5f, 0.0f,
    0.75f, -0.5f, 0.0f,
    0.75f, 0.5f, 0.0f
};
unsigned int Basic::DEFAULT_INDICES[6] = {
	0, 1, 2,
	3, 4, 5
};

Basic::Basic()
    : Basic(800,
            600,
            DEFAULT_VERTEX_SHADER,
            DEFAULT_FRAGMENT_SHADER) { }

Basic::Basic(int window_width, int window_height)
    : Basic(window_width,
            window_height,
            DEFAULT_VERTEX_SHADER,
            DEFAULT_FRAGMENT_SHADER) { }

Basic::Basic(std::string vertex_shader_source, std::string fragment_shader_source)
    : Basic(800,
            600,
            vertex_shader_source,
            fragment_shader_source) { }

Basic::Basic(float        vertices[],
             int          vertices_size,
             unsigned int indices[],
             int          indices_size)
    : Basic(800,
            600,
            vertices,
            vertices_size,
            indices,
            indices_size) { }

Basic::Basic(int          window_width,
             int          window_height,
             float        vertices[],
             int          vertices_size,
             unsigned int indices[],
             int          indices_size)
    : Basic(window_width,
            window_height,
            vertices,
            vertices_size,
            indices,
            indices_size,
            DEFAULT_VERTEX_SHADER,
            DEFAULT_FRAGMENT_SHADER) { }

Basic::Basic(int         window_width,
             int         window_height,
             std::string vertex_shader_source,
             std::string fragment_shader_source)
    : Basic(window_width,
            window_height,
            DEFAULT_VERTICES,
            sizeof(DEFAULT_VERTICES),
            DEFAULT_INDICES,
            sizeof(DEFAULT_INDICES),
            vertex_shader_source,
            fragment_shader_source) { }


Basic::Basic(int window_width, int window_height, float vertices[], int vertices_size, unsigned int indices[], int indices_size, std::string vertex_shader_source, std::string fragment_shader_source)
    : _window_width(window_width),
      _window_height(window_height),
      _vertices(vertices),
      _vertices_size(vertices_size),
      _indices(indices),
      _indices_size(indices_size),
      _vertex_shader_source(vertex_shader_source),
      _fragment_shader_source(fragment_shader_source) { }

int Basic::RealMain(int argc, const char* argv[])
{
	_InitGLFW();

	_InitWindow("LearnOpenGL", NULL, NULL);

	if (_InitGlad() == false) return -1; // 这个一定要放在 _InitWindow 后面

	_InitViewPort();

	_InitShaderProgram();

	_InitBuffer();

	_InitBufferData();

	_InitRenderConfig();

	_RenderLoop();

	_Terminal();

	return 0;
}

void Basic::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Basic::UpdateProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true); // 如果按下 ESC，就关闭窗口
}

void Basic::_InitGLFW()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 限定 OpenGL 版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 限定 OpenGL 版本
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

bool Basic::_InitGlad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { // 传入 GLFW 指针以初始化 GLAD
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	return true;
}

void Basic::_InitWindow(const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
	_window = glfwCreateWindow(_window_width, _window_height, title, monitor, share);
	if (_window == NULL) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(_window);
}

void Basic::_InitViewPort()
{
	glViewport(0, 0, _window_width, _window_height);
	glfwSetFramebufferSizeCallback(_window, Basic::FramebufferSizeCallback);
}

unsigned int Basic::_CreateVertexShader(const char* shader_source)
{
	/* 插入 Vertex Shader */
	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER); // 创建一个 Vertex Shader
	glShaderSource(vertex_shader, 1, &shader_source, NULL);        // 给 Shader 插入 GLSL 代码
	glCompileShader(vertex_shader);                                // 编译 GLSL 代码

	/* 如果 Vertex Shader 编译出错，则反馈错误信息 */
	int  success;
	char info_log[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
		          << info_log << std::endl;
	}

	return vertex_shader;
}

unsigned int Basic::_CreateFragmentShader(const char* shader_source)
{
	/* 插入 Fragment Shader */
	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &shader_source, NULL);
	glCompileShader(fragment_shader);

	/* 如果 Fragment Shader 编译出错，则反馈错误信息 */
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

unsigned int Basic::_CreateShaderProgram(std::initializer_list<unsigned int> shader_li)
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
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
		          << info_log << std::endl;
	}

	return shader_program;
}

void Basic::_InitShaderProgram()
{
	unsigned int vertex_shader   = _CreateVertexShader(_vertex_shader_source.c_str());
	unsigned int fragment_shader = _CreateFragmentShader(_fragment_shader_source.c_str());

	_shader_program = _CreateShaderProgram({ vertex_shader, fragment_shader });

	glDeleteShader(vertex_shader);   // 删除着色器
	glDeleteShader(fragment_shader); // 删除着色器
}

void Basic::_InitBuffer()
{
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
	glGenBuffers(1, &_IBO);
}

void Basic::_InitBufferData()
{
	// NOTE Bind 属于拷贝数据的一部分（而不是初始化）
	glBindVertexArray(_VAO); // 这里要先绑定 VAO
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
	glBufferData(GL_ARRAY_BUFFER, _vertices_size, _vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices_size, _indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Basic::_InitRenderConfig()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // 填充模式（默认）
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 线框模式
}

void Basic::_RenderLoop()
{
	while (!glfwWindowShouldClose(_window)) {
		_UpdateBeforeRender();
		_UpdateClear();
		_UpdateRender();
		_UpdateAfterRender();
	}
}

void Basic::_UpdateBeforeRender()
{
	UpdateProcessInput(_window); // Handle Input
}

void Basic::_UpdateClear()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 设置无色区域的默认颜色
	glClear(GL_COLOR_BUFFER_BIT);         // 清空缓冲区的某个缓冲
}

void Basic::_UpdateRender()
{
	glUseProgram(_shader_program);
	glBindVertexArray(_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Basic::_UpdateAfterRender()
{
	glfwSwapBuffers(_window); // 交换缓冲
	glfwPollEvents();         // 调用事件
}

void Basic::_Terminal()
{
	/* （可选）手动返还资源 */
	//glDeleteVertexArrays(1, &_VAO);
	//glDeleteBuffers(1, &_VBO);
	//glDeleteProgram(_shader_program);

	glfwTerminate(); // 渲染循环结束后，返还所有资源
}

} // namespace gl_template