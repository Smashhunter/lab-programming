cmake_minimum_required(VERSION 3.15)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 2025.2.${PATCH_VERSION})

project(lab2 VERSION ${PROJECT_VESRION})

file(GLOB SOURCES "src/*.cpp")
add_executable(ip_filter ${SOURCES})
target_include_directories(ip_filter PRIVATE 
    ${CMAKE_SOURCE_DIR}/include)

set_target_properties(ip_filter PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

find_package(Boost 1.74 REQUIRED COMPONENTS unit_test_framework)


if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

if (MSVC)
    set(CPACK_GENERATOR ZIP)
else ()
    set(CPACK_GENERATOR DEB)
endif ()

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT savelybur.work@gmail.com)
set(CPACK_PACKAGE_DESCRIPTION "Simple program to filter ip's")

include(CPack)

add_subdirectory(tests)
