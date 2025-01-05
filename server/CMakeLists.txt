#限定cmake 版本最低2.8
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

#项目名称
project(main)

#向编译单元添加包含目录的路径。这允许源文件包含来自指定目录的头文件
include_directories(Include)

#用于将指定目录下的所有源文件列表赋值给一个变量
aux_source_directory(Include/Libuv SRC_LIST1)
aux_source_directory(Include/Time SRC_LIST2)
aux_source_directory(Include/TestLuaApi SRC_LIST3)
aux_source_directory(Include/Space SRC_LIST4)

#从指定目录查找对应的库
find_library(LIB libuv.so ./Lib)
find_library(LIB1 libcore.so ./Lib)
#find_library(LUA_LIBRARY NAMES lua liblua REQUIRED)
find_library(LUA_LIBRARY liblua.so PATHS ./Lib NO_DEFAULT_PATH)


message(${LUA_LIBRARY})
if(LIB)
	message("find libuv.so")
else()
	message("not find libuv.so")
endif()

#添加一个可执行目标以及它的源文件
add_executable(main Main.cpp ${SRC_LIST1} ${SRC_LIST2} ${SRC_LIST3} ${SRC_LIST4})

#为指定的目标添加链接库， 这里增加libuv.so库
#target_link_libraries(main ${LIB} ${LIB1} ${LUA_LIBRARY})
target_link_libraries(main ${LIB} ${LUA_LIBRARY})

#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
