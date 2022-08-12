# Add Subdirectory
# NOTE 通过改动这里来修改编译
#add_subdirectory("opengl-learning/ch01-01-VboTest")
add_subdirectory("opengl-learning/ch01-02-IboTest")


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
        Ch01-02-IboTest # NOTE 通过改动这里来修改编译
)
