find_package(Qt6 REQUIRED COMPONENTS Core Test)

add_executable(test_calculator
    test_calculator.cpp
    ${CMAKE_SOURCE_DIR}/calculator.cpp
)

target_include_directories(test_calculator PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(test_calculator PRIVATE Qt6::Core Qt6::Test)

add_test(NAME CalculatorTests COMMAND test_calculator)
