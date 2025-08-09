project(RealEngineTests)

file(GLOB_RECURSE TEST_SOURCES *.cpp)

add_executable(RealEngineTests ${TEST_SOURCES})

target_link_libraries(RealEngineTests
    gtest
    gtest_main
    RealEngine
)

include(GoogleTest)
gtest_discover_tests(RealEngineTests)
