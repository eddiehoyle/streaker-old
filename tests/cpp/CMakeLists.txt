include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

message(Google:\ ${gtest_SOURCE_DIR}/include)
message(Google:\ ${gtest_SOURCE_DIR})

add_executable(streaker_tests streakerTest.cc)

target_link_libraries(streaker_tests gtest gtest_main)
#target_link_libraries(streaker_tests streak)
