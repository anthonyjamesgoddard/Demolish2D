set(HDRS
    collision_pair.h
    object.h
    scenario.h)

set(SRCS
    collision_pair.cpp
    object.cpp
    scenario.cpp)

add_library(world ${SRCS} ${HDRS})
target_link_libraries(world geometry)
