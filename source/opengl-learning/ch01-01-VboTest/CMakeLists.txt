# Add Library
add_library(Ch01-01-VboTest STATIC "vbo_test.cpp")
set_target_properties(Ch01-01-VboTest PROPERTIES LINKER_LANGUAGE CXX)


# Link Target
target_include_directories(Ch01-01-VboTest
   PRIVATE ${GLAD_INC}
   PRIVATE ${GLFW_INC}
)
target_link_libraries(Ch01-01-VboTest
    PRIVATE ${LIB_GLAD}
    PRIVATE ${LIB_GLFW}
)
