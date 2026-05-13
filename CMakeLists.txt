cmake_minimum_required(VERSION 3.10)
project(thi-lab3 VERSION 1.0.0 LANGUAGES CXX)

# Опции (опционально)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Директории с заголовками
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Список исходников библиотеки
file(GLOB LIB_SOURCES "src/lib/*.cpp")
# Список публичных заголовков (для установки и IDE)
file(GLOB LIB_PUBLIC_HEADERS "include/lib/*.hpp")

# Добавляем библиотеку как SHARED
add_library(electro SHARED ${LIB_SOURCES} ${LIB_PUBLIC_HEADERS}
    include/electro/dlltest.hpp)

# Указываем пути к заголовочным файлам
target_include_directories(electro
    PUBLIC
        $<BUILD_INTERFACE:${INCLUDE_DIR}>      # для компиляции самой библиотеки
        $<INSTALL_INTERFACE:include>            # для установленных файлов
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/lib     # приватные заголовки (если есть)
)

add_executable(myapp "src/main/main.cpp")

# Подключаем библиотеку
target_link_libraries(myapp PRIVATE electro)

# Для приложения тоже нужны публичные заголовки библиотеки
target_include_directories(myapp PRIVATE ${INCLUDE_DIR})
