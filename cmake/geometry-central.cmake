if (TARGET geometry-central)
  return()
endif()

include(CPM)

CPMAddPackage(
  NAME geometry-central
  GIT_TAG 1f8a50c353e90322294c1c5aa0d411b7894f24ed
  GITHUB_REPOSITORY "nmwsharp/geometry-central"
)
