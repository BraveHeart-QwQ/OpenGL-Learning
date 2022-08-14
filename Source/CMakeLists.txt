# Add Subdirectory
# CRITICAL 通过改动这里来修改编译
add_subdirectory("OpenglLearning/CH01_02_IboTest")


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
        Ch01_02_IboTest # CRITICAL 通过改动这里来修改编译
)
