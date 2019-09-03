cmake_minimum_required(VERSION 3.3...3.12 FATAL_ERROR)


project (graphDrawing)


find_package(VTK QUIET)

include(${VTK_USE_FILE})
add_executable(graphDrawing MACOSX_BUNDLE graphDrawing.cxx)
target_link_libraries(graphDrawing ${VTK_LIBRARIES})
