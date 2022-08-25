# Get All .cpp File in folder
file(GLOB CPP_FILES *.cpp)


# Add Library
add_library(GL_TEMPLATE STATIC ${CPP_FILES})
set_target_properties(GL_TEMPLATE PROPERTIES LINKER_LANGUAGE CXX)


# Link Target
target_include_directories(GL_TEMPLATE
    PRIVATE ${GLAD_INC}
    PRIVATE ${GLFW_INC}
)
target_link_libraries(GL_TEMPLATE
    PRIVATE ${LIB_GLAD}
    PRIVATE ${LIB_GLFW}
)
