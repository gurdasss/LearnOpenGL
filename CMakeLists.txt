# Specify the minimum required version of CMake.
# A modern version (3.5 or higher) is recommended.
cmake_minimum_required(VERSION 4.0)

# Define your project. Explicitly declare it as a C++ project.
# The `VERSION` and `DESCRIPTION` are good practice for larger projects.
project(LearnOpenGL LANGUAGES CXX C) # Add LANGUAGES CXX for clarity

# ==============================================================================
# C++ Standard Compliance
# ==============================================================================

# Enforce C++23 standard.
# CMAKE_CXX_STANDARD: Sets the C++ standard version to use.
# CMAKE_CXX_STANDARD_REQUIRED: If ON, CMake will fail if the compiler doesn't support the requested standard.
# CMAKE_CXX_EXTENSIONS: If OFF, disables compiler-specific extensions, enforcing strict standard compliance.
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enabled Debug Build
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug/Release)" FORCE)
endif ()

# ==============================================================================
# Dependency Management (GLFW and OpenGL) ✨
# ==============================================================================
#set(GLFW_DIR "/usr/local/lib/cmake/glfw3" CACHE PATH "Path to the directory containing glfw3Config.cmake")
# Use find_package to locate the required libraries on the system.

# 1. Find GLFW (Version 3 or higher is expected)
# The REQUIRED keyword ensures the configuration fails if the library isn't found.
find_package(glfw3 3.3 REQUIRED)

# 2. Find OpenGL (Usually provided by the system, often via GL or OpenGL::GL)
# We find it using the standard component name, 'GL'.
find_package(OpenGL REQUIRED)

# 3. Find X11 (Required for windowing on Linux/X11 systems)
# We find all necessary components for a stable X11 setup.
if (UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
endif()


# ==============================================================================
# Dependency Management (GLFW and OpenGL) ✨
# ==============================================================================

# Build glad.c into a static library
add_library(glad STATIC
        dependencies/glad/src/gl.c
)

# Make the include dir available when compiling glad AND to consumers that link to 'glad'.
# Use PUBLIC so both the target itself and its consumers get the include path.
target_include_directories(glad PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glad/include
)

# ==============================================================================
# Compiler Warnings and Best Practices
# ==============================================================================

# Define a common set of compiler warnings for best practices.
# These flags are generally compatible with GCC, Clang, and MSVC (though MSVC uses different syntax).
# We'll use generator expressions for compiler-specific flags to ensure portability.

# Common warnings (GCC/Clang style)
set(COMMON_CXX_WARNINGS
        -Wall                 # Enable all common warnings
        -Wextra               # Enable extra warnings
        -Wpedantic            # Enforce strict standard compliance (pedantic warnings)
        -Wshadow              # Warn when a local variable shadows another variable
        -Wnon-virtual-dtor    # Warn if a class has virtual functions but a non-virtual destructor
        -Wold-style-cast      # Warn for C-style casts in C++
        -Wcast-align          # Warn when a pointer cast results in a stricter alignment requirement
        -Wunused              # Warn about unused variables, functions, etc.
        -Woverloaded-virtual  # Warn when a virtual function is overloaded but not overridden
        -Wconversion          # Warn for implicit conversions that might change value
        -Wsign-conversion     # Warn for conversions between signed and unsigned types that might change value
        -Wnull-dereference    # Warn if a dereference of a null pointer is detected
        -Wdouble-promotion    # Warn if float is implicitly promoted to double
        -Wformat=2            # More stringent format string checks
        -Werror               # Treat warnings as errors (highly recommended for robust code)
        -Weffc++
)

# ==============================================================================
# Executable Definition and Linking
# ==============================================================================

# NEW: Set the output directory for the executable.
# We set this to a 'bin' directory inside the project's source directory.
# The `CMAKE_CURRENT_SOURCE_DIR` variable points to the directory containing
# this CMakeLists.txt file.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

# Add your executable.
add_executable(${PROJECT_NAME} main.cpp
#        dependencies/glad/src/gl.c
)

# Link the required libraries to your executable.
# Modern CMake uses the targets provided by the find_package commands.

# PRIVATE means these libraries are only needed for compiling/linking this executable.
target_link_libraries(${PROJECT_NAME} PRIVATE
        glad
        # GLFW linking (modern CMake provides the "target" `glfw`)
        glfw
        # OpenGL linking (modern CMake provides the "target" `OpenGL::GL`)
        OpenGL::GL
)

# Add any platform-specific dependencies (mainly for Linux/X11)
if (UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${X11_LIBRARIES})
    # Add other common dependencies often needed by GLFW on Linux
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread dl rt m)
endif()
