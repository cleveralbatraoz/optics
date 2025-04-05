find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_library(OpticsLib
    lens.cpp
    lens.h
    paraxial_characteristics.h
    float.h
    float.cpp
    ray.h
    matrix_operations.h
    matrix_operations.cpp
)

target_include_directories(OpticsLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(OpticsLib PUBLIC
    Qt6::Core
    Qt6::Widgets
)

add_executable(${PROJECT_NAME}
    input_window.cpp
    input_window.h
    lens_painter.cpp
    lens_painter.h
    output_window.cpp
    output_window.h
    main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE OpticsLib)
