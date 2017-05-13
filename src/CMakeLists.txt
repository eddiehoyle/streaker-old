
include_directories(${STREAKER_INCLUDE_DIR})

if(PYTHONLIBS_FOUND)
    include_directories(${PYTHON_INCLUDE_DIRS})
endif()

if(Boost_FOUND)
    set(Boost_USE_STATIC_LIBS OFF)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME OFF)

    include_directories(${Boost_INCLUDE_DIRS})

    add_library(streak SHARED streaker.cc streak.cc range.cc)
    target_include_directories(
            streak PUBLIC
            ${STREAKER_INCLUDE_DIR}
            ${Boost_INCLUDE_DIRS}
    )
    target_link_libraries(
            streak PUBLIC
            ${Boost_LIBRARIES}
    )

    add_executable(streaker main.cc)
    target_link_libraries(
            streaker LINK_PUBLIC
            streak
    )
endif()
