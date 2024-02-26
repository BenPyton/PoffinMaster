cmake_minimum_required(VERSION 3.5)

project(Test_Backend LANGUAGES CXX)

enable_testing()

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Test Quick)
find_package(Qt6 REQUIRED COMPONENTS Test Quick)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Test_Backend tst_backend.cpp)
add_test(NAME Test_Backend COMMAND Test_Backend)

# Allowing to include the Backend headers
target_include_directories(Test_Backend PRIVATE "..")

target_link_libraries(Test_Backend PRIVATE
    Qt6::Test
    Qt6::Quick
    backendplugin
)

