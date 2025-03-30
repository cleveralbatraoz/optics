cmake_minimum_required(VERSION 3.19)
project(lens LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

qt_add_executable(lens
    WIN32 MACOSX_BUNDLE
    main.cpp
    lens.h
    lens.cpp
    paraxial_characteristics.h
    output_window.h output_window.cpp
    lens_painter.h lens_painter.cpp
    input_window.h input_window.cpp
    refraction.h




)

target_link_libraries(lens
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS lens
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET lens
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
