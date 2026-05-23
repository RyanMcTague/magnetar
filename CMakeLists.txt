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
    PRIVATE
        src/input/input_system.cpp
        src/input/keyboard_device.cpp
        src/input/mouse_device.cpp
        src/input/input_action.cpp

        src/events/event_system.cpp

        src/core/window.cpp
        src/core/time.cpp

        src/filesystems/native_file_system.cpp
        src/filesystems/memory_file_system.cpp

        src/utils/string_utils.cpp

        src/platforms/glfw_window.cpp
        src/platforms/glfw_keyboard_device.cpp
        src/platforms/glfw_mouse_device.cpp

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
)

########################################################
# Defines
########################################################
target_compile_definitions(magnetar PRIVATE MAGNETAR_BUILD)

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
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


########################################################
# Install headers
########################################################
install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
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