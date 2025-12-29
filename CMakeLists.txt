cmake_minimum_required(VERSION 3.18)

set(MAJOR_VERSION "2025")
set(MINOR_VERSION "5")
set(PATCH_VERSION "1")

project(physics 
    VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}
    DESCRIPTION "Physics Project"
)

if(DEFINED PATCH_VERSION_OVERRIDE)
    set(PROJECT_VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION_OVERRIDE})
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin)

# Пытаемся найти предустановленный SFML
find_package(SFML COMPONENTS graphics)

if (SFML_FOUND)
    message(STATUS "The SFML installed in the system will be used")
else ()
    # Если SFML не найден - выкачиваем и собираем из исходников
    message(STATUS "Get SFML from the source code")
    include(FetchContent)
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.x
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
    FetchContent_MakeAvailable(SFML)
    set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    # Обход потенциальных проблем при сборке sfml-graphics
    # (stb_image.h: 'argument': conversion from 'int' to 'short')
    set(WARNINGS_AS_ERRORS FALSE CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(SFML)
endif ()

# К сожалению, вплоть до C++20 https://en.cppreference.com/w/cpp/numeric/constants
# нет удобного кроссплатформенного способа получить число pi.
# define ниже нужен для включения M_PI
if (MSVC)
    add_definitions(-D_USE_MATH_DEFINES)
endif ()

include_directories(include)
include_directories(black_box)
file(GLOB SOURCES "src/*.cpp" "black_box/*cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)

target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
        )

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY data DESTINATION .)

# execute_process(
#   COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/update_tag.py
# )
# execute_process(
#   COMMAND git describe --abbrev=0 --tags
#   OUTPUT_VARIABLE tag
# )
# string(LENGTH ${tag} tag_len)
# math(EXPR new_tag_len "${tag_len} - 1")
# string(SUBSTRING "${tag}" 0 ${new_tag_len} clear_tag)
# string(REPLACE "." ";" list_tag "${clear_tag}")
# list(GET list_tag 0 MAJOR_VERSION)
# list(GET list_tag 1 MINOR_VERSION)
# list(GET list_tag 2 PATCH_VERSION)
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT savelybur.work@gmail.com)
set(CPACK_PACKAGE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

if (MSVC OR MSYS)
    set(CPACK_GENERATOR ZIP)
else ()
    set(CPACK_GENERATOR DEB)
endif()

include(CPack)
