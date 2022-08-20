# Add Library
add_library(TEMPLATE_BASIC STATIC "Basic.cpp")
set_target_properties(TEMPLATE_BASIC PROPERTIES LINKER_LANGUAGE CXX)


# Link Target
target_include_directories(TEMPLATE_BASIC
    PRIVATE ${GLAD_INC}
    PRIVATE ${GLFW_INC}
)
target_link_libraries(TEMPLATE_BASIC
    PRIVATE ${LIB_GLAD}
    PRIVATE ${LIB_GLFW}
)
