set(EXAMPLES
  gaussianFilter
  bilateralFilter
)

foreach(EXAMPLE ${EXAMPLES})
    add_executable(${EXAMPLE} ${EXAMPLE}.cpp)
    if(UNIX)
      target_link_libraries(${EXAMPLE} -lm)
    endif()
endforeach()
