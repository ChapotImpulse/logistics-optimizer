find_package(GTest REQUIRED)

file(GLOB TEST_SRC "*.cpp")
add_executable(test_runner ${TEST_SRC})
target_link_libraries(test_runner GTest::GTest GTest::Main ${PROJECT_NAME})
target_include_directories(test_runner PRIVATE ../src)

add_test(NAME LogisticsTests COMMAND test_runner)
