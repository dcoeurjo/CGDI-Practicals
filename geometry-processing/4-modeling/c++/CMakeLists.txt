
add_executable(simpleTest simpleTest.cpp)
target_link_libraries(simpleTest polyscope)

add_executable(displayOBJ displayOBJ.cpp)
target_link_libraries(displayOBJ polyscope geometry-central)
