cmake_minimum_required(VERSION 3.5)

project(UCOTutorias LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# --- CORRECCIÓN AQUÍ ---
# La palabra REQUIRED va antes de COMPONENTS
find_package(Qt5 REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    GestorDatos.h
)

add_executable(UCOTutorias ${PROJECT_SOURCES})

target_link_libraries(UCOTutorias PRIVATE Qt5::Widgets)