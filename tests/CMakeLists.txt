find_package(Qt6 REQUIRED COMPONENTS Test)

add_executable(OpticsTest
    test_paraxial_characteristics.cpp
)

target_link_libraries(OpticsTest PRIVATE
    OpticsLib
    Qt6::Test
)
