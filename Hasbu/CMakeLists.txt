# Include the config file
include(${CMAKE_SOURCE_DIR}/config.cmake)

# Create the HasbuLib library
add_library(HasbuLib STATIC)

option(USE_OPENGL "Use OpenGL" ON)
option(USE_VULKAN "Use Vulkan" OFF)

# Add subdirectories
add_subdirectory(src/API)
add_subdirectory(src/Application)
add_subdirectory(src/Utilities)
add_subdirectory(src/Renderer)

# Create the precompiled header
target_precompile_headers(HasbuLib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/defines.hpp)

# Set up include directories
set(HASBULIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(HASBULIB_INCLUDE_VENDOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor)

target_include_directories(HasbuLib PUBLIC
    ${HASBULIB_INCLUDE_DIR}
    ${HASBULIB_INCLUDE_VENDOR_DIR}
    ${HASBULIB_INCLUDE_DIR}/Utilities
    ${HASBULIB_INCLUDE_DIR}/Application
    ${HASBULIB_INCLUDE_DIR}/API
    ${HASBULIB_INCLUDE_DIR}/Renderer
    ${HASBULIB_INCLUDE_VENDOR_DIR}/LA/src

    # ${HASBULIB_INCLUDE_VENDOR_DIR}/Json
    ${HASBULIB_INCLUDE_VENDOR_DIR}/stb_image
)

# Find required packages and link them
list(APPEND REQUIRED_LIBS glfw3 spdlog)

foreach(PKG ${REQUIRED_LIBS})
    find_package(${PKG} REQUIRED)

    if(${PKG}_FOUND)
        message(STATUS "${PKG} library found. Version: ${${PKG}_VERSION}")

        if(${PKG} STREQUAL "glfw3")
            target_link_libraries(HasbuLib PUBLIC glfw)
        elseif(${PKG} STREQUAL "spdlog")
            target_link_libraries(HasbuLib PUBLIC spdlog::spdlog)
        endif()
    else()
        message(FATAL_ERROR "${PKG} library not found")
    endif()
endforeach()

# Validate the api to use
if(USE_VULKAN)
    find_package(Vulkan REQUIRED)
    message(STATUS "Using Vulkan HASBULIB")

    if(Vulkan_FOUND)
        target_compile_definitions(HasbuLib PRIVATE VULKAN)
        message(STATUS "Vulkan library found. Version: ${Vulkan_VERSION}")
        target_link_libraries(HasbuLib PUBLIC Vulkan::Vulkan)
    else()
        message(FATAL_ERROR "Vulkan library not found")
    endif()

elseif(USE_OPENGL)
    message(STATUS "Using OpenGL HASBULIB")

    find_package(GLEW 2.2 REQUIRED)

    if(GLEW_FOUND)
        message(STATUS "OPENGL GLEW library found. Version: ${GLEW_VERSION}")
        target_link_libraries(HasbuLib PUBLIC GLEW::GLEW)
        target_compile_definitions(HasbuLib PRIVATE OPENGL)
    else()
        message(FATAL_ERROR "OPENGL GLEW library not found")
    endif()
endif()