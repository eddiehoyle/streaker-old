
add_library(pystreak SHARED pystreak.cc)
target_include_directories(
        pystreak PUBLIC
        ${STREAKER_INCLUDE_DIR}
        ${PYTHON_INCLUDE_PATH}
        ${Boost_INCLUDE_DIRS}
)
target_link_libraries(
        pystreak
        ${Boost_LIBRARIES}
        ${PYTHON_LIBRARIES}
)
