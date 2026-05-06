add_executable(tests 
    test_transport.cpp
    test_simulation.cpp
)

target_include_directories(tests PRIVATE ../src)

include(GoogleTest)
gtest_discover_tests(tests)
