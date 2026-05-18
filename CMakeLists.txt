cmake_minimum_required(VERSION 3.28)

project(
    Magnetar 
    VERSION 1.0
    LANGUAGES CXX
)

include(FetchContent)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

########################################################
# Options 
########################################################
option(MAGNETAR_BUILD_SHARED "Build shared library" OFF)
option(MAGNETAR_BUILD_TESTS "Build tests" ON)

########################################################
# Constants
########################################################
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(MAGNETAR_BUILD_ARCH "macOS")
    message(STATUS "Building ${PROJECT_NAME} for macOS")
else()
    message(FATAL_ERROR "${PROJECT_NAME} does not support ${CMAKE_SYSTEM_NAME}")
endif()

########################################################
# Dependencies
########################################################
find_package(fmt CONFIG QUIET)
if(NOT fmt_FOUND)
    FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 12.1.0
    )
    FetchContent_MakeAvailable(fmt)
endif()

find_package(spdlog CONFIG QUIET)
if(NOT spdlog_FOUND)
    FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.17.0
    )

    FetchContent_MakeAvailable(spdlog)
endif()

if(MAGNETAR_BUILD_TESTS)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
    )

    if(MAKE_SYSTEM_NAME STREQUAL  "Windows")
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()
    FetchContent_MakeAvailable(googletest)
endif()

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
        include/magnetar/magnetar.h
        include/magnetar/core/application.h
        include/magnetar/core/base.h
        include/magnetar/core/file_system.h
        include/magnetar/core/filesystems/native_file_system.h
        include/magnetar/core/filesystems/memory_file_system.h
        include/magnetar/utils/string_utils.h

        src/core/application.cpp
        src/core/filesystems/native_file_system.cpp
        src/core/filesystems/memory_file_system.cpp
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
# Dependencies
########################################################
target_link_libraries(magnetar
    PUBLIC
        fmt::fmt
        spdlog::spdlog
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

if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(magnetar PUBLIC MAGNETAR_BUILD_DEBUG)
    message(STATUS "Building ${PROJECT_NAME} in Debug mode")
elseif()
    target_compile_definitions(magnetar PUBLIC MAGNETAR_BUILD_RELEASE)
    message(STATUS "Building ${PROJECT_NAME} in Release mode")
endif()

install(
    TARGETS magnetar
    EXPORT MagnetarTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

########################################################
# Testing
########################################################
if(MAGNETAR_BUILD_TESTS)
    enable_testing()

    add_executable(magnetar_tests
        tests/core/filesystems/memory_file_system_test.cpp
    )

    target_link_libraries(magnetar_tests GTest::gtest_main magnetar)

    include(GoogleTest)
    gtest_discover_tests(magnetar_tests)    
endif()

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