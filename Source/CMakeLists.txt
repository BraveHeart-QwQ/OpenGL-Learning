# Add Subdirectory
# NOTE 通过改动这里来修改编译
add_subdirectory("Practice/LearnOpengl/1_HelloTriangle_1")


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
        Learngl_Practice_HelloTriangle_1 # NOTE 通过改动这里来修改编译
)
