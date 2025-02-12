project(CGDI-c++)

CMAKE_MINIMUM_REQUIRED(VERSION 3.14)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include_directories(${PROJECT_SOURCE_DIR}/deps)
message(STATUS "Deps: ${PROJECT_SOURCE_DIR}/deps")

############################################################
#Image processing
add_subdirectory(image-processing/1-SlicedOptimalTransport/c++/)
add_subdirectory(image-processing/2-BilateralFilter/c++/)
add_subdirectory(image-processing/3-Rasterization/c++/)
############################################################

# Disabling 3D for now

############################################################
#Geometry processing

include(geometry-central)
include(polyscope)

add_subdirectory(geometry-processing/4-modeling/c++/)
add_subdirectory(geometry-processing/5-LaplacianSmoothing/c++/)
add_subdirectory(geometry-processing/6-GeomProcessing/c++)
add_subdirectory(geometry-processing/7-MonteCarloGeometryProcessing/c++)
############################################################
