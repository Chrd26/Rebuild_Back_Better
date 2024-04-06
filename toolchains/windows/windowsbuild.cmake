set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_CXX_COMPILER clang++)

# where is the target environment located
set(CMAKE_FIND_ROOT_PATH /usr/local/Cellar/llvm/17.0.6_1/bin/clang-cl)
# adjust the default behavior of the FIND_XXX() commands:
# search programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
