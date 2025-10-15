cmake_minimum_required(VERSION 3.15)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 2025.3.${PATCH_VERSION})

project(lab3 VERSION ${PROJECT_VESRION})

#creating lib for our project
# file(GLOB LIB_SOURCES "src/lib/*.cpp")
# add_library(my_lib STATIC ${LIB_SOURCES})
# target_include_directories(my_lib PUBLIC 
#     ${CMAKE_SOURCE_DIR}/include)

#configuring main to use our lib
add_executable(main "src/main/main.cpp")
target_include_directories(main PRIVATE 
    ${CMAKE_SOURCE_DIR}/include)
# target_link_libraries(main PRIVATE my_lib)

set_target_properties(main PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

#find_package(Boost 1.74 REQUIRED COMPONENTS unit_test_framework)


if (MSVC)
    target_compile_options(main PRIVATE
        /W4
    )
else ()
    target_compile_options(main PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS main RUNTIME DESTINATION bin)

if (WIN32)
    set(CPACK_GENERATOR ZIP)
else ()
    set(CPACK_GENERATOR DEB)
endif ()

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT savelybur.work@gmail.com)
set(CPACK_PACKAGE_DESCRIPTION "Simple program that represents some data structures")

include(CPack)

add_subdirectory(tests)
