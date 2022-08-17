# Add Library
add_library(Template_Basic STATIC "Basic.cpp")
set_target_properties(Template_Basic PROPERTIES LINKER_LANGUAGE CXX)


# Link Target
target_include_directories(Template_Basic
    PRIVATE ${GLAD_INC}
    PRIVATE ${GLFW_INC}
)
target_link_libraries(Template_Basic
    PRIVATE ${LIB_GLAD}
    PRIVATE ${LIB_GLFW}
)
