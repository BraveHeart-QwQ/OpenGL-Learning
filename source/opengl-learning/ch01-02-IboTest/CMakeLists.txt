# Add Library
add_library(Ch01-02-IboTest STATIC "ibo_test.cpp")
set_target_properties(Ch01-02-IboTest PROPERTIES LINKER_LANGUAGE CXX)


# Link Target
target_include_directories(Ch01-02-IboTest
   PRIVATE ${GLAD_INC}
   PRIVATE ${GLFW_INC}
)
target_link_libraries(Ch01-02-IboTest
    PRIVATE ${LIB_GLAD}
    PRIVATE ${LIB_GLFW}
)
