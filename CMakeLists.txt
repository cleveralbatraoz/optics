cmake_minimum_required(VERSION 3.21)
project(Optics LANGUAGES CXX)

# Find Qt components
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

# Optional but recommended for Qt Creator
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
