# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Video_Deconstructor_Widget_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Video_Deconstructor_Widget_autogen.dir\\ParseCache.txt"
  "Video_Deconstructor_Widget_autogen"
  )
endif()
