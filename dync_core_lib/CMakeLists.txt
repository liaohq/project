cmake_minimum_required(VERSION 2.8)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.)
include_directories(Include)
aux_source_directory(. SRC_LIST1)



aux_source_directory(Include/Base/Time/ SRC_LIST2)

find_library(LUA_LIBRARIES liblua.so PATHS ./Lib NO_DEFAULT_PATH)

message(STATUS "h ${LUA_LIBRARIES}, ${LUA_INCLUDE_DIR}" )

add_library(core SHARED  ${SRC_LIST1} ${SRC_LIST2})



#target_link_libraries(core PRIVATE ${LUA_LIBRARIES})
target_link_libraries(core ${LUA_LIBRARIES})

# 设置包含目录，以便编译器可以找到 Lua 的头文件  
#target_include_directories(core PRIVATE ${LUA_INCLUDE_DIR})

