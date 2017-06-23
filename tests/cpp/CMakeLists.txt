include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

add_executable(streaker_tests testMain.cc testRange.cc testStreak.cc testPadding.cc testParser.cc)

target_link_libraries(streaker_tests gtest gtest_main)
target_link_libraries(streaker_tests streak)
