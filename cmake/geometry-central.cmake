if (TARGET geometry-central)
  return()
endif()

include(CPM)

CPMAddPackage(
  NAME geometry-central
  VERSION 1.0.0
  GITHUB_REPOSITORY "nmwsharp/geometry-central"
)
