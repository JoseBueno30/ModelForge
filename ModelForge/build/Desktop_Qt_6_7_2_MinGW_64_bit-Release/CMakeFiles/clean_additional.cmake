# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\ModelForge_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ModelForge_autogen.dir\\ParseCache.txt"
  "ModelForge_autogen"
  )
endif()
