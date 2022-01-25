PROJECT(rasterizer)
cmake_minimum_required(VERSION 3.1)

set (CMAKE_CXX_STANDARD 11)

set(EXAMPLES
  rasterizer
)


include_directories(${PROJECT_SOURCE_DIR})

foreach(EXAMPLE ${EXAMPLES})
    add_executable(${EXAMPLE} ${EXAMPLE}.cpp)
    if(UNIX)
      target_link_libraries(${EXAMPLE} -lm)
    endif()
endforeach()
