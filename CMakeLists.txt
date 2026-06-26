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
add_subdirectory(magnetar)

########################################################
# Includes
########################################################
target_include_directories(magnetar 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/magnetar/include>
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