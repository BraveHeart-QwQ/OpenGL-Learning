#ifndef GLLEARNING_GLLEARNING_CH1IBOTEST
#define GLLEARNING_GLLEARNING_CH1IBOTEST

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace ch1_ibo_test {

/// @brief 重制窗口大小回调
void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

/// @brief 处理输入
void ProcessInput(GLFWwindow* window);

/// @brief 在 main 中调用
int RealMain(int argc, const char* argv[]);

} // namespace ch1_ibo_test

#endif
