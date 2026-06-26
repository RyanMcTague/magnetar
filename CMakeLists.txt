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
# SDK Export (non-CMake users)
# Usage: cmake --install <build> --prefix ./sdk --component sdk
########################################################
install(
    TARGETS magnetar
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT sdk
)

# Use install(CODE) + file(COPY FOLLOW_SYMLINK_CHAIN) so Conan cache symlinks
# are dereferenced into real files instead of dangling symlinks in the SDK.
install(CODE "
    file(COPY \"${CMAKE_CURRENT_SOURCE_DIR}/magnetar/include/\"
        DESTINATION \"\${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}\"
        FOLLOW_SYMLINK_CHAIN
        FILES_MATCHING PATTERN \"*.h\" PATTERN \"*.hpp\" PATTERN \"*.inl\"
    )
" COMPONENT sdk)

set(_MAGNETAR_SDK_TARGETS
    fmt::fmt
    spdlog::spdlog
    glfw
    magic_enum::magic_enum
    glm::glm
    yaml-cpp::yaml-cpp
    assimp::assimp
    EnTT::EnTT
    Freetype::Freetype
)

foreach(_dep IN LISTS _MAGNETAR_SDK_TARGETS)
    get_target_property(_incs ${_dep} INTERFACE_INCLUDE_DIRECTORIES)
    if(_incs)
        foreach(_dir IN LISTS _incs)
            # Only copy from Conan cache or our own source tree.
            # Reject system-wide prefixes (/usr, /opt, /System, /Library) — those
            # are picked up when a dep resolves to a system install (e.g. Homebrew)
            # instead of its Conan package, and copying them wholesale pulls in
            # thousands of unrelated headers (at-spi2, gtk, etc.).
            if(NOT _dir MATCHES "\\$<" AND EXISTS "${_dir}"
               AND NOT _dir MATCHES "^/usr/"
               AND NOT _dir MATCHES "^/opt/"
               AND NOT _dir MATCHES "^/System/"
               AND NOT _dir MATCHES "^/Library/")
                install(CODE "
                    file(COPY \"${_dir}/\"
                        DESTINATION \"\${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}\"
                        FOLLOW_SYMLINK_CHAIN
                        FILES_MATCHING PATTERN \"*.h\" PATTERN \"*.hpp\" PATTERN \"*.inl\"
                    )
                " COMPONENT sdk)
            endif()
        endforeach()
    endif()

    foreach(_prop IN ITEMS IMPORTED_LOCATION IMPORTED_LOCATION_RELEASE IMPORTED_LOCATION_DEBUG IMPORTED_LOCATION_RELWITHDEBINFO)
        get_target_property(_lib ${_dep} ${_prop})
        if(_lib AND EXISTS "${_lib}")
            # Same guard: skip system-installed libs, only bundle Conan-managed ones
            if(NOT _lib MATCHES "^/usr/" AND NOT _lib MATCHES "^/opt/"
               AND NOT _lib MATCHES "^/System/" AND NOT _lib MATCHES "^/Library/")
                install(FILES "${_lib}" DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT sdk)
            endif()
            break()
        endif()
    endforeach()
endforeach()

# Mono headers and library
install(CODE "
    file(COPY \"${MONO_INCLUDE_DIR}/\"
        DESTINATION \"\${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/mono-2.0\"
        FOLLOW_SYMLINK_CHAIN
        FILES_MATCHING PATTERN \"*.h\"
    )
" COMPONENT sdk)
install(FILES "${MONO_LIBRARY}" DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT sdk)

# C# script core assembly
install(
    FILES "${CMAKE_BINARY_DIR}/Magnetar-ScriptCore.dll"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT sdk
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