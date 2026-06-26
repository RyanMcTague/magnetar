cmake_minimum_required(VERSION 3.28)

project(
    Magnetar 
    VERSION 1.0
    LANGUAGES CXX
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(MONO_ROOT "${CMAKE_SOURCE_DIR}/vendor/mono")

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
find_package(yaml-cpp REQUIRED CONFIG)
find_package(assimp REQUIRED CONFIG)
find_package(EnTT REQUIRED CONFIG)
find_package(freetype REQUIRED CONFIG)

find_path(
    MONO_INCLUDE_DIR
    mono/jit/jit.h
    PATHS
        "${MONO_ROOT}/include/mono-2.0"
    REQUIRED
)

find_library(
    MONO_LIBRARY
    NAMES monosgen-2.0
    PATHS
        "${MONO_ROOT}/lib"
    NO_DEFAULT_PATH
    REQUIRED
)
message(STATUS "Mono include: ${MONO_INCLUDE_DIR}")
message(STATUS "Mono library: ${MONO_LIBRARY}")

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
            include/magnetar/assets/asset.h
            include/magnetar/assets/asset_manager.h
            include/magnetar/assets/resouce_loader.h
            include/magnetar/assets/asset_handle.h
            include/magnetar/assets/loaders/texture_loader.h
            include/magnetar/assets/loaders/shader_loader.h
            include/magnetar/assets/loaders/material_loader.h
            include/magnetar/assets/loaders/mesh_loader.h
            include/magnetar/assets/loaders/font_loader.h

            include/magnetar/containers/tree.h

            include/magnetar/core/time.h
            include/magnetar/core/application.h
            include/magnetar/core/window.h
            include/magnetar/core/logger.h
            include/magnetar/core/base.h
            include/magnetar/core/uuid.h
            include/magnetar/core/layer.h
            include/magnetar/core/layer_stack.h
            include/magnetar/core/game_layer.h

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

            include/magnetar/math/rect.h

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
            include/magnetar/renderer/font.h
            include/magnetar/renderer/render_command.h
            include/magnetar/renderer/buffer_mask.h
            include/magnetar/renderer/renderer.h
            include/magnetar/renderer/camera.h
            include/magnetar/renderer/material.h
            include/magnetar/renderer/vertex_array.h
            include/magnetar/renderer/vertex_buffer.h
            include/magnetar/renderer/renderer2d.h

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

            include/magnetar/scene/scene.h
            include/magnetar/scene/components.h
            include/magnetar/scene/entity_handle.h
            include/magnetar/scene/entity.h

            include/magnetar/scripting/script_class.h
            include/magnetar/scripting/script_instance.h
            include/magnetar/scripting/script_runtime.h

            include/magnetar/scripting/enums.h
            include/magnetar/scripting/script_engine.h
            include/magnetar/scripting/script_registry.h
            include/magnetar/scripting/script_field.h
            
            include/magnetar/scripting/mono/mono_runtime.h
            include/magnetar/scripting/mono/mono_script_class.h
            include/magnetar/scripting/mono/mono_script_instance.h

            include/magnetar/utils/enum_utils.h
            include/magnetar/utils/string_utils.h
            include/magnetar/utils/image_utils.h

            include/magnetar/vendor/stb_image.h
            
            include/magnetar/magnetar.h
             
    PRIVATE
        src/assets/asset_manager.cpp
        src/assets/loaders/texture_loader.cpp
        src/assets/loaders/shader_loader.cpp
        src/assets/loaders/material_loader.cpp
        src/assets/loaders/mesh_loader.cpp
        src/assets/loaders/font_loader.cpp

        src/core/application.cpp
        src/core/logger.cpp
        src/core/window.cpp
        src/core/time.cpp
        src/core/layer_stack.cpp
        src/core/uuid.cpp
        src/core/game_layer.cpp

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
        src/renderer/renderer.cpp
        src/renderer/material.cpp
        src/renderer/camera.cpp
        src/renderer/font.cpp
        src/renderer/renderer2d.cpp
        
        src/renderer/backend/opengl/glad.cpp
        src/renderer/backend/opengl/helpers.cpp
        src/renderer/backend/opengl/shader_compiler.cpp
        src/renderer/backend/opengl/shader.cpp
        src/renderer/backend/opengl/index_buffer.cpp
        src/renderer/backend/opengl/vertex_buffer.cpp
        src/renderer/backend/opengl/vertex_array.cpp
        src/renderer/backend/opengl/texture.cpp
        src/renderer/backend/opengl/graphics_device.cpp

        src/scene/scene.cpp
        src/scene/entity.cpp

        src/scripting/script_engine.cpp
        src/scripting/script_registry.cpp

        src/scripting/mono/mono_runtime.cpp
        src/scripting/mono/mono_script_class.cpp
        src/scripting/mono/mono_script_instance.cpp
        
        src/utils/string_utils.cpp
        src/utils/image_utils.cpp
)

########################################################
# Includes
########################################################
target_include_directories(magnetar 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${MONO_INCLUDE_DIR}
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
        -Wno-zero-length-array
        -Wgnu-anonymous-struct
        -Wno-nested-anon-types
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
        yaml-cpp::yaml-cpp
        assimp::assimp
        EnTT::EnTT
        Freetype::Freetype
        ${MONO_LIBRARY}
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
# Mono C# Assembly
########################################################
find_program(MCS_EXECUTABLE mcs REQUIRED)

file(GLOB_RECURSE MAGNETAR_CS_SOURCES
    "${CMAKE_SOURCE_DIR}/scripting/*.cs"
)
list(FILTER MAGNETAR_CS_SOURCES EXCLUDE REGEX ".*/obj/.*")

set(MAGNETAR_CS_OUTPUT "${CMAKE_BINARY_DIR}/Magnetar-ScriptCore.dll")

add_custom_command(
    OUTPUT "${MAGNETAR_CS_OUTPUT}"
    COMMAND "${MCS_EXECUTABLE}"
        -target:library
        -out:${MAGNETAR_CS_OUTPUT}
        ${MAGNETAR_CS_SOURCES}
    DEPENDS ${MAGNETAR_CS_SOURCES}
    COMMENT "Compiling Magnetar C# assembly with Mono"
    VERBATIM
)

add_custom_target(magnetar_csharp ALL
    DEPENDS "${MAGNETAR_CS_OUTPUT}"
)

########################################################
# Sandbox
########################################################
if(MAGNETAR_BUILD_SANDBOX)
    add_executable(sample sample/main.cpp sample/assets.h)
    target_compile_features(sample PUBLIC cxx_std_20)
    target_link_libraries(sample PRIVATE Magnetar::Magnetar)
    set_target_properties(sample PROPERTIES
        BUILD_RPATH "${MONO_ROOT}/lib"
        INSTALL_RPATH "${MONO_ROOT}/lib"
    )

    file(GLOB_RECURSE SAMPLE_CS_SOURCES
        "${CMAKE_SOURCE_DIR}/sample/*.cs"
    )
    list(FILTER SAMPLE_CS_SOURCES EXCLUDE REGEX ".*/obj/.*")

    set(SAMPLE_CS_OUTPUT "${CMAKE_BINARY_DIR}/Sample.dll")

    add_custom_command(
        OUTPUT "${SAMPLE_CS_OUTPUT}"
        COMMAND "${MCS_EXECUTABLE}"
            -target:library
            -out:${SAMPLE_CS_OUTPUT}
            -r:${MAGNETAR_CS_OUTPUT}
            ${SAMPLE_CS_SOURCES}
        DEPENDS ${SAMPLE_CS_SOURCES}
        COMMENT "Compiling Magnetar C# assembly with Mono"
        VERBATIM
    )

    add_custom_target(sample_csharp ALL
        DEPENDS "${SAMPLE_CS_OUTPUT}"
    )
    add_dependencies(sample_csharp magnetar_csharp)

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