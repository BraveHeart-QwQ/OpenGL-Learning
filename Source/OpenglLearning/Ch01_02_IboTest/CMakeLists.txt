# Add Library
add_library(Ch01_02_IboTest STATIC "IboTest.cpp")
set_target_properties(Ch01_02_IboTest PROPERTIES LINKER_LANGUAGE CXX)


# Link Target
target_include_directories(Ch01_02_IboTest
   PRIVATE ${GLAD_INC}
   PRIVATE ${GLFW_INC}
)
target_link_libraries(Ch01_02_IboTest
    PRIVATE ${LIB_GLAD}
    PRIVATE ${LIB_GLFW}
)
