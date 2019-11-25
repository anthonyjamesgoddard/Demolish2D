set(HDRS
    vertex.h
    sector.h
    polygon.h)

set(HDRS
    vertex.cpp
    sector.cpp
    polygon.cpp)

add_library(geometry ${SRCS} ${HDRS})
