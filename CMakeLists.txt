# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.12)

# Set the project name
project(libpax)

# Add the source files for the library
set(SOURCES
    src/fb.cpp
    src/keypad.cpp
)

# Create the static library
add_library(libpax STATIC ${SOURCES})

# Set include directories for the library
target_include_directories(libpax PUBLIC include)

# Set additional compiler flags or options
target_compile_options(libpax PRIVATE -O3 -Wall -Wextra)
