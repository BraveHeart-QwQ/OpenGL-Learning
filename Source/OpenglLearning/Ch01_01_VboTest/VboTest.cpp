#include "VboTest.hpp"
#include <iostream>

namespace ch1_vbo_test {

/*---------- Internal Function ----------*/

void UpdateRender(unsigned int shader_program, unsigned int VAO, unsigned int VBO, GLsizeiptr size, const void* data, GLenum usage)
{
	// 0. 复制顶点数组到缓冲中供 OpenGL 使用
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	// 1. 设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 2. 当我们渲染一个物体时要使用着色器程序
	glUseProgram(shader_program);
	// 3. 绑定 VAO
	glBindVertexArray(VAO);
	// 4. 绘制物体
	// CRITICAL 这里添加或修改绘制物体的函数
}

void UpdateStaticRender(unsigned int shader_program, unsigned int VAO)
{
	//glUseProgram(shader_program);
	//glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3); // CRITICAL 这里添加或修改绘制物体的函数
}

void InitGLFW()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 限定 OpenGL 版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 限定 OpenGL 版本
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

GLFWwindow* InitWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
	GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, share);
	if (window == NULL) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);
	return window;
}

bool InitGlad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { // 传入 GLFW 指针以初始化 GLAD
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	return true;
}

unsigned int GetVertexShader()
{
	/* 一个简单的 Vertex Shader */
	const char* vertex_shader_source =
	    "#version 330 core\n"
	    "layout (location = 0) in vec3 aPos;\n"
	    "void main()\n"
	    "{\n"
	    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	    "}\0";

	/* 插入 Vertex Shader */
	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER); // 创建一个 Vertex Shader
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL); // 给 Shader 插入 GLSL 代码
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

unsigned int GetFragmentShader()
{
	/* 插入一个简单的 Fragment Shader */
	const char* fragment_shader_source =
	    "#version 330 core\n"
	    "out vec4 FragColor;\n"
	    "void main()\n"
	    "{\n"
	    "	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	    "}\0";

	/* 插入 Fragment Shader */
	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
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

unsigned int GetShaderProgram(std::initializer_list<unsigned int> shader_li)
{
	unsigned int shader_program = glCreateProgram();
	std::for_each(shader_li.begin(), shader_li.end(), [shader_program](unsigned int i) {
		glAttachShader(shader_program, i);
	});
	glLinkProgram(shader_program);
	return shader_program;
}

/*---------- Header Definition ----------*/

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true); // 如果按下 ESC，就关闭窗口
}

int RealMain(int argc, const char* argv[])
{
	InitGLFW();                                                           // 初始化 GLFW
	GLFWwindow* window = InitWindow(800, 600, "LearnOpenGL", NULL, NULL); // 创建并初始化一个窗口
	if (InitGlad() == false) return -1;                                   // 初始化 GLAD，如果失败就退出程序

	/* 设置 ViewPort */
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback); // 监听窗口是否改变

	/* 初始化着色器 */
	unsigned int vertex_shader   = GetVertexShader();
	unsigned int fragment_shader = GetFragmentShader();
	unsigned int shader_program  = GetShaderProgram({vertex_shader, fragment_shader});
	glUseProgram(shader_program);
	glDeleteShader(vertex_shader);   // 删除着色器
	glDeleteShader(fragment_shader); // 删除着色器

	/* 初始化 VBO 和 VAO */
	unsigned int VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	/* 循环前初始化（如果不频繁改变物体，则只运行一次） */
	float vertices[] = {
	    -0.5f, -0.5f, 0.0f, // left
	    0.5f, -0.5f, 0.0f,  // right
	    0.0f, 0.5f, 0.0f    // top
	};
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 导入顶点数据
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/* 渲染循环 */
	while (!glfwWindowShouldClose(window)) {
		ProcessInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 设置无色区域的默认颜色
		glClear(GL_COLOR_BUFFER_BIT);         // 清空缓冲区的某个缓冲

		//UpdateRender(shader_program, VAO, VBO, xxx, xxx, GL_STATIC_DRAW); // CRITICAL 物体频繁修改时的单帧渲染
		UpdateStaticRender(shader_program, VAO); // CRITICAL 物体不修改时的单帧渲染

		glfwPollEvents();        // 调用事件
		glfwSwapBuffers(window); // 交换缓冲
	}

	/* （可选）手动返还资源 */
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shader_program);

	glfwTerminate(); // 渲染循环结束后，返还所有资源

	return 0;
}

} // namespace ch1_vbo_test