if(USE_OPENGL)
    message(STATUS "Using OpenGL API")

    file(GLOB SOURCE_FILES "ImGuiLayerOpenGL.cpp")
    target_sources(HasbuLib PUBLIC ${SOURCE_FILES})

# target_sources(HasbuLib PUBLIC OpenGL/OpenGLContext.cpp)
elseif(USE_VULKAN)
    message(STATUS "Using Vulkan API")
    file(GLOB SOURCE_FILES "ImGuiLayerVulkan.cpp")
    target_sources(HasbuLib PUBLIC ${SOURCE_FILES})
endif()
