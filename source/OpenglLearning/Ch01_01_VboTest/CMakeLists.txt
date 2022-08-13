# Add Library
add_library(Ch01_01_VboTest STATIC "VboTest.cpp")
set_target_properties(Ch01_01_VboTest PROPERTIES LINKER_LANGUAGE CXX)


# Link Target
target_include_directories(Ch01_01_VboTest
   PRIVATE ${GLAD_INC}
   PRIVATE ${GLFW_INC}
)
target_link_libraries(Ch01_01_VboTest
    PRIVATE ${LIB_GLAD}
    PRIVATE ${LIB_GLFW}
)
