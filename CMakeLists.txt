cmake_minimum_required(VERSION 3.16)

project(ConsolCalc
    VERSION 1.0.0
    DESCRIPTION "Консольный калькулятор на Qt с сигналами/слотами"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Автоматический вызов moc / uic / rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Ищем Qt 6 (для Qt 5 замени на find_package(Qt5 ...))
find_package(Qt6 REQUIRED COMPONENTS Core)

# --- Собственно приложение ---
add_executable(ConsolCalc
    main.cpp
    calculator.cpp
    csvparser.cpp
)

target_link_libraries(ConsolCalc PRIVATE Qt6::Core)

# --- Тесты ---
enable_testing()
add_subdirectory(tests)

# --- Упаковка (CPack) ---
set(CPACK_PACKAGE_NAME        "ConsolCalc")
set(CPACK_PACKAGE_VENDOR      "Student")
set(CPACK_PACKAGE_VERSION     "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION "${PROJECT_DESCRIPTION}")
set(CPACK_PACKAGE_CONTACT     "student@example.com")

if(WIN32)
    set(CPACK_GENERATOR "ZIP")
elseif(APPLE)
    set(CPACK_GENERATOR "DragNDrop")
else()
    set(CPACK_GENERATOR "TGZ;DEB")
endif()

include(CPack)
