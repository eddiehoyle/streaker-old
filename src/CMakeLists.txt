
include_directories(${STREAKER_INCLUDE_DIR})
include_directories(${PYTHON_INCLUDE_DIRS})

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

include_directories(${Boost_INCLUDE_DIRS})

file(GLOB STREAKER_FILE_SOURCE_FILES "file/*.cc")
file(GLOB STREAKER_ROOT_SOURCE_FILES "*.cc")
set(STREAKER_SOURCE_FILES
        ${STREAKER_FILE_SOURCE_FILES}
        ${STREAKER_ROOT_SOURCE_FILES})
add_library(streak SHARED ${STREAKER_SOURCE_FILES})
target_include_directories(streak PUBLIC
        ${STREAKER_INCLUDE_DIR}
        ${Boost_INCLUDE_DIRS})
target_link_libraries(streak PUBLIC ${Boost_LIBRARIES})

add_executable(streaker main.cc)
target_link_libraries(streaker streak)

message(WARNING ${STREAKER_SOURCE_FILES})