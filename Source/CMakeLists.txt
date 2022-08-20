# Add Subdirectory

# 在 Source/CMakeLists.txt 中添加 Template/Basic 库，然后在 Practice 的各个应用点链接

## Add Template Library
add_subdirectory("Template/1_Basic")

## CRITICAL 在这里添加库
add_subdirectory("Practice/LearnOpengl/1_HelloTriangle_1")
add_subdirectory("Practice/LearnOpengl/1_HelloTriangle_2")
add_subdirectory("Practice/LearnOpengl/1_HelloTriangle_3")


# Add Executable
add_executable(Run "main.cpp")
set_target_properties(Run PROPERTIES LINKER_LANGUAGE CXX)


# Link Target
target_include_directories(Run
   PRIVATE ${GLAD_INC}
   PRIVATE ${GLFW_INC}
)
target_link_libraries(Run
    PRIVATE
        ${LIB_GLAD}
        ${LIB_GLFW}
        LEARNGL_PRACTICE_HELLOTRIANGLE_1 # CRITICAL 通过改动这里来修改编译
        LEARNGL_PRACTICE_HELLOTRIANGLE_2
        LEARNGL_PRACTICE_HELLOTRIANGLE_3
)
