# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.18
cmake_policy(SET CMP0009 NEW)

# SOURCE_FILES at CMakeLists.txt:16 (file)
file(GLOB NEW_GLOB LIST_DIRECTORIES true "/home/vlad/workspace/stm32/walle/src/*.c")
set(OLD_GLOB
  "/home/vlad/workspace/stm32/walle/src/init_it.c"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/vlad/workspace/stm32/walle/build/CMakeFiles/cmake.verify_globs")
endif()

# SOURCE_FILES at CMakeLists.txt:16 (file)
file(GLOB NEW_GLOB LIST_DIRECTORIES true "/home/vlad/workspace/stm32/walle/src/*.cpp")
set(OLD_GLOB
  "/home/vlad/workspace/stm32/walle/src/main.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/vlad/workspace/stm32/walle/build/CMakeFiles/cmake.verify_globs")
endif()
