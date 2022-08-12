#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

/*---------- Function Declaration ----------*/
/// @brief 重制窗口大小
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

/// @brief 处理输入
void processInput(GLFWwindow* window);


int main(int argc, const char* argv[])
{
	/* GLFW 初始化 */
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	/* GLFW 创建窗口对象 */
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	/* 传入 GLFW 指针以初始化 GLAD */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	/* 设置 ViewPort */
	glViewport(0, 0, 800, 600);

	/* 监听窗口改变的事件 */
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/* 渲染循环 */
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		// ... 单帧渲染

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 设置无色区域的默认颜色
		glClear(GL_COLOR_BUFFER_BIT);         // 清空缓冲区的某个缓冲

		glfwPollEvents();        // 调用事件
		glfwSwapBuffers(window); // 交换缓冲
	}

	/* 渲染循环结束后，返还所有资源 */
	glfwTerminate();

	std::cout << "Hello World" << std::endl;

	return 0;
}

/*---------- Function Definition ----------*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true); // 如果按下 ESC，就关闭窗口
}
