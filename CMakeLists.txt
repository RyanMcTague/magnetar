cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Magnetar VERSION 1.0)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

add_library(Magnetar STATIC
    src/core/application.cpp
    include/magnetar/core/application.h
    include/magnetar/magnetar.h
)

add_library(Magnetar::Magnetar ALIAS Magnetar)

target_include_directories(Magnetar 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

install(
    TARGETS Magnetar
    EXPORT MagnetarTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT MagnetarTargets
    FILE MagnetarTargets.cmake
    NAMESPACE Magnetar::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Magnetar
)

configure_package_config_file(
    cmake/MagnetarConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/MagnetarConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Magnetar
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/MagnetarConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/MagnetarConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/MagnetarConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Magnetar
)