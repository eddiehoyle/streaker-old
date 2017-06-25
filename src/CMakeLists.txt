
include_directories(${STREAKER_INCLUDE_DIR})
include_directories(${PYTHON_INCLUDE_DIRS})

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

include_directories(${Boost_INCLUDE_DIRS})

file(GLOB SOURCE_FILES "*.cc")
add_library(streak SHARED ${SOURCE_FILES} ../include/parser.hh ../include/frame.hh frame.cc parser.cc ../include/path.hh path.cc)
target_include_directories(streak PUBLIC ${STREAKER_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})
target_link_libraries(streak PUBLIC ${Boost_LIBRARIES})

add_executable(streaker main.cc)
target_link_libraries(streaker streak)
