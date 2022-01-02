cmake_minimum_required(VERSION 3.20)
project(DS)

set(CMAKE_CXX_STANDARD 14)

#add_executable(HW1 HW1/rat.cpp)
#add_executable(HW2 HW2/bst.cpp)
#add_executable(HW3-1 HW3/p76091420_hw3-1.cpp)
#add_executable(HW3-2 HW3/p76091420_hw3-2.cpp)
#add_executable(HW3-3 HW3/p76091420_hw3-3.cpp)
#add_executable(HW3-4 HW3/p76091420_hw3-4.cpp)
#add_executable(HW3-5 HW3/p76091420_hw3-5.cpp)
#add_executable(test test/char_pointer.c)

#add_executable(test1 test/test_callby.cpp)
#add_executable(test2 test/test_load_int.cpp)
#add_executable(test3 test/main0.cpp)


file (GLOB_RECURSE files *.cpp)
foreach (file ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    add_executable (${exe} ${file})
    message (\ \ \ \ --\ src/${exe}.cpp\ will\ be\ compiled\ to\ bin/${exe})
endforeach ()

