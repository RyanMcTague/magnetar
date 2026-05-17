cmake_minimum_required(VERSION 3.28)

project(
    Magnetar 
    VERSION 1.0
    LANGUAGES CXX
)

include(FetchContent)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

#
# Options 
#
option(MAGNETAR_BUILD_SHARED "Build shared library" OFF)

#
# Dependencies
#
find_package(fmt CONFIG QUIET)
find_package(spdlog CONFIG QUIET)

if(NOT fmt_FOUND OR NOT spdlog_FOUND)
    FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 12.1.0
    )

    FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.17.0
    )

    FetchContent_MakeAvailable(fmt spdlog)

endif()

#
# Library
#
if(MAGNETAR_BUILD_SHARED)
    add_library(magnetar SHARED)
else()
    add_library(magnetar STATIC)
endif()

add_library(Magnetar::Magnetar ALIAS magnetar)

#
# Source Files
#
target_sources(magnetar 
    PRIVATE
       src/core/application.cpp
)

#
# Includes
#
target_include_directories(magnetar 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

#
# C++ Standard
#
target_compile_features(magnetar PUBLIC cxx_std_20)

#
# Dependencies
#
target_link_libraries(magnetar
    PUBLIC
        fmt::fmt
        spdlog::spdlog
)

install(
    TARGETS magnetar
    EXPORT MagnetarTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

#
# Install headers
#
install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

#
# Export targets
#
install(
    EXPORT MagnetarTargets
    FILE MagnetarTargets.cmake
    NAMESPACE Magnetar::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Magnetar
)

#
# Config
#
configure_package_config_file(
    cmake/MagnetarConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/MagnetarConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Magnetar
)

#
# Version
#
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/MagnetarConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

#
# Install config
#
install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/MagnetarConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/MagnetarConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Magnetar
)