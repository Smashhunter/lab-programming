add_executable(tests
    test_ip.cpp
)

# Подключение Boost
target_link_libraries(tests
    Boost::unit_test_framework

)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Добавление тестового задания CTest
add_test(NAME Tests COMMAND tests)
