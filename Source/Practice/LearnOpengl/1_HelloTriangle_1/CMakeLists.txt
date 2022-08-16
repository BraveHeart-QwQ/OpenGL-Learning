add_subdirectory("../../../Template/1_Basic" binary_dir)


add_library(Learngl_Practice_HelloTriangle_1 STATIC "Practice.cpp")
set_target_properties(Learngl_Practice_HelloTriangle_1 PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(Learngl_Practice_HelloTriangle_1
    PRIVATE ${GLAD_INC}
    PRIVATE ${GLFW_INC}
)
target_link_libraries(Learngl_Practice_HelloTriangle_1
    PRIVATE ${LIB_GLAD}
    PRIVATE ${LIB_GLFW}
    PRIVATE Template_Basic
)
