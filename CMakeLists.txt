cmake_minimum_required(VERSION 3.10)
project(thi-lab3 VERSION 1.0.0 LANGUAGES CXX)

# Опции (опционально)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Директории с заголовками
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Список исходников библиотеки
file(GLOB LIB_SOURCES "src/lib/*.cpp")

add_executable(mp3-player "src/main/main.cpp")

# Для приложения тоже нужны публичные заголовки библиотеки
target_include_directories(mp3-player PRIVATE ${INCLUDE_DIR})
target_link_libraries(mp3-player PRIVATE SFML::Audio)
target_sources(mp3-player PRIVATE ${LIB_SOURCES})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT mp3-player)
