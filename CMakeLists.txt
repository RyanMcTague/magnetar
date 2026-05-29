cmake_minimum_required(VERSION 3.28)

project(
    Magnetar 
    VERSION 1.0
    LANGUAGES CXX
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

########################################################
# Options 
########################################################
option(MAGNETAR_BUILD_SHARED "Build shared library" OFF)
option(MAGNETAR_BUILD_SANDBOX "Build sandbox" ON)

########################################################
# Dependencies
########################################################
find_package(fmt REQUIRED CONFIG)
find_package(spdlog REQUIRED CONFIG)
find_package(glfw3 REQUIRED CONFIG)
find_package(magic_enum REQUIRED CONFIG)
find_package(glm REQUIRED CONFIG)

########################################################
# Library
########################################################
if(MAGNETAR_BUILD_SHARED)
    add_library(magnetar SHARED)
else()
    add_library(magnetar STATIC)
endif()

add_library(Magnetar::Magnetar ALIAS magnetar)

########################################################
# Source Files
########################################################
target_sources(magnetar 
    PUBLIC 
        FILE_SET HEADERS
        BASE_DIRS include
        FILES
            include/magnetar/containers/tree.h

            include/magnetar/core/time.h
            include/magnetar/core/application.h
            include/magnetar/core/window.h
            include/magnetar/core/logger.h
            include/magnetar/core/base.h
            include/magnetar/core/uuid.h

            include/magnetar/events/event_handle.h
            include/magnetar/events/event_system.h
            include/magnetar/events/event_callback.h

            include/magnetar/filesystem/memory_file_system.h
            include/magnetar/filesystem/native_file_system.h
            include/magnetar/filesystem/file_system.h

            include/magnetar/input/input_device.h
            include/magnetar/input/input_action.h
            include/magnetar/input/input_code.h
            include/magnetar/input/enums.h
            include/magnetar/input/mouse_device.h
            include/magnetar/input/mapped_input_code.h
            include/magnetar/input/keyboard_device.h
            include/magnetar/input/input_system.h

            include/magnetar/platforms/glfw/glfw_keyboard_device.h
            include/magnetar/platforms/glfw/glfw_mouse_device.h
            include/magnetar/platforms/glfw/glfw_window.h

            include/magnetar/renderer/buffer_layout.h
            include/magnetar/renderer/enums.h
            include/magnetar/renderer/graphics_device.h
            include/magnetar/renderer/index_buffer.h
            include/magnetar/renderer/shader_library.h
            include/magnetar/renderer/shader.h
            include/magnetar/renderer/texture.h
            include/magnetar/renderer/mesh.h
            include/magnetar/renderer/vertex_array.h
            include/magnetar/renderer/vertex_buffer.h

            include/magnetar/renderer/backend/opengl/glad.h
            include/magnetar/renderer/backend/opengl/helpers.h
            include/magnetar/renderer/backend/opengl/texture.h
            include/magnetar/renderer/backend/opengl/index_buffer.h
            include/magnetar/renderer/backend/opengl/khrplatform.h
            include/magnetar/renderer/backend/opengl/shader_compiler.h
            include/magnetar/renderer/backend/opengl/shader.h
            include/magnetar/renderer/backend/opengl/vertex_buffer.h
            include/magnetar/renderer/backend/opengl/vertex_array.h
            include/magnetar/renderer/backend/opengl/graphics_device.h

            include/magnetar/utils/enum_utils.h
            include/magnetar/utils/string_utils.h
            
            include/magnetar/magnetar.h
             
    PRIVATE
        src/core/application.cpp
        src/core/logger.cpp
        src/core/window.cpp
        src/core/time.cpp
        src/core/uuid.cpp

        src/events/event_system.cpp

        src/filesystems/file_system.cpp
        src/filesystems/native_file_system.cpp
        src/filesystems/memory_file_system.cpp

        src/input/input_system.cpp
        src/input/keyboard_device.cpp
        src/input/mouse_device.cpp
        src/input/input_action.cpp

        src/platforms/glfw/glfw_window.cpp
        src/platforms/glfw/glfw_keyboard_device.cpp
        src/platforms/glfw/glfw_mouse_device.cpp

        src/renderer/shader.cpp
        src/renderer/shader_library.cpp
        src/renderer/buffer_layout.cpp
        src/renderer/mesh.cpp
        
        src/renderer/backend/opengl/glad.cpp
        src/renderer/backend/opengl/helpers.cpp
        src/renderer/backend/opengl/shader_compiler.cpp
        src/renderer/backend/opengl/shader.cpp
        src/renderer/backend/opengl/index_buffer.cpp
        src/renderer/backend/opengl/vertex_buffer.cpp
        src/renderer/backend/opengl/vertex_array.cpp
        src/renderer/backend/opengl/texture.cpp
        src/renderer/backend/opengl/graphics_device.cpp
        
        src/utils/string_utils.cpp
)

########################################################
# Includes
########################################################
target_include_directories(magnetar 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

########################################################
# C++ Standard
########################################################
target_compile_features(magnetar PUBLIC cxx_std_20)

########################################################
# Properties
########################################################
set_target_properties(magnetar PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
########################################################
# C++ Warnings
########################################################
if(MSVC)
    target_compile_options(magnetar PRIVATE /W4)
else()
    target_compile_options(magnetar PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

########################################################
# Dependencies
########################################################
target_link_libraries(magnetar
    PUBLIC
        fmt::fmt
        spdlog::spdlog
        glfw
        magic_enum::magic_enum
        glm::glm
)

########################################################
# Defines
########################################################
target_compile_definitions(magnetar PRIVATE MAGNETAR_BUILD)
target_compile_definitions(magnetar PUBLIC GLFW_INCLUDE_NONE)

if(MAGNETAR_BUILD_SHARED)
    target_compile_definitions(magnetar PUBLIC MAGNETAR_BUILD_SHARED)
else()
    target_compile_definitions(magnetar PUBLIC MAGNETAR_BUILD_STATIC)
endif()

target_compile_definitions(magnetar
    PUBLIC
        $<$<CONFIG:Debug>:MAGNETAR_BUILD_DEBUG>
        $<$<CONFIG:Release>:MAGNETAR_BUILD_RELEASE>
)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_compile_definitions(magnetar
        PUBLIC
            MAGNETAR_PLATFORM_MACOS
    )
else()
    message(FATAL_ERROR "${PROJECT_NAME} does not support ${CMAKE_SYSTEM_NAME}")
endif()


########################################################
# Sandbox
########################################################
if(MAGNETAR_BUILD_SANDBOX)
    add_executable(sample sample/main.cpp)
    target_compile_features(sample PUBLIC cxx_std_20)
    target_link_libraries(sample PRIVATE Magnetar::Magnetar)
endif()

########################################################
# Install
########################################################
install(
    TARGETS magnetar
    EXPORT MagnetarTargets
    FILE_SET HEADERS
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

########################################################
# Export targets
########################################################
install(
    EXPORT MagnetarTargets
    FILE MagnetarTargets.cmake
    NAMESPACE Magnetar::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Magnetar
)

########################################################
# Config
########################################################
configure_package_config_file(
    cmake/MagnetarConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/MagnetarConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Magnetar
)

########################################################
# Version
########################################################
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/MagnetarConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

########################################################
# Install config
########################################################
install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/MagnetarConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/MagnetarConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Magnetar
)