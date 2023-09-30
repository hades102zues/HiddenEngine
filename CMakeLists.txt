# -- Basic Project Pre-requisites -- #
cmake_minimum_required(VERSION 3.10)
project(HiddenEngine VERSION 0.0.1)

# -- Compiler Flags -- #
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -g")

# -- Build Folder --#

# -- Process Additional CMakeList files -- #
    # -- Cmake creates a local ledger where it keeps track of any dependencies/rules/targets it encounters
# -- Process these cmakefiles and add their items to the ledger
add_subdirectory(third-party)
add_subdirectory(src)

# configure building 
# cmake -H<location of the root Cmakefile> -B<directory to be used to hold build files>





