
add_executable(demolish driver.cpp)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

target_link_libraries(demolish ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} world)

