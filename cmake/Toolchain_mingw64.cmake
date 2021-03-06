# http://www.cmake.org/Wiki/CmakeMingw
# http://www.cmake.org/Wiki/CMake_Cross_Compiling#The_toolchain_file

# the name of the target operating system
SET(CMAKE_SYSTEM_NAME Windows)

# which compilers to use for C and C++
# Settings for Ubuntu 12.04.1 LTS
#SET(CMAKE_C_COMPILER /usr/bin/x86_64-w64-mingw32-gcc)
#SET(CMAKE_CXX_COMPILER /usr/bin/x86_64-w64-mingw32-gcc)
#SET(CMAKE_RC_COMPILER /usr/bin/x86_64-w64-mingw32-windres)
# Settings for OpenSuSE 13.2
SET(CMAKE_C_COMPILER /usr/bin/x86_64-w64-mingw32-gcc)
SET(CMAKE_CXX_COMPILER /usr/bin/x86_64-w64-mingw32-c++ )

# here is the target environment located
# Settings for Ubuntu 12.04.1 LTS
#SET(CMAKE_FIND_ROOT_PATH  /usr/i686-w64-mingw32 /usr/i686-w64-mingw32/include)
# Settings for OpenSuSE 13.2
SET(CMAKE_FIND_ROOT_PATH  /usr/lib64/gcc/x86_64-w64-mingw32/4.9.2/include /usr/lib64/gcc/x86_64-w64-mingw32/4.9.2/include/c++ )

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search 
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

