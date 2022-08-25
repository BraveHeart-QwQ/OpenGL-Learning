file(GLOB CPP_FILES *.cpp)

# Add Library
add_library(GLLEARNING_CH01 STATIC ${CPP_FILES})
set_target_properties(GLLEARNING_CH01 PROPERTIES LINKER_LANGUAGE CXX)


# Link Target
target_include_directories(GLLEARNING_CH01
   PRIVATE ${GLAD_INC}
   PRIVATE ${GLFW_INC}
)
target_link_libraries(GLLEARNING_CH01
    PRIVATE ${LIB_GLAD}
    PRIVATE ${LIB_GLFW}
)
