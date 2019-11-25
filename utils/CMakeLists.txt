set(HDRS
    matrix.h
    timer.h)

set(SRCS
    matrix.cpp
    timer.cpp)

add_library(utils ${SRCS} ${HDRS})
target_link_libraries(utils geometry)
