# Add Subdirectory

## CRITICAL Add Template Library
add_subdirectory("Template")
add_subdirectory("Practice/LearnOpengl/Chapter1")
add_subdirectory("Tutorial/LearnOpenGL/Chapter1")
add_subdirectory("Tutorial/LearnOpenGL/Chapter2")


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
        GLLEARNING_CH02 # CRITICAL 通过改动这里来修改编译
)
