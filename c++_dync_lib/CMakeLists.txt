cmake_minimum_required(VERSION 2.8)


include_directories(.)

find_path(LUA_INCLUDE_DIR lua.h PATHS /root/lua-5.4.6/src NO_DEFAULT_PATH)
find_library(LUA_LIBRARIES liblua.so PATHS /root/lua-5.4.6/src  NO_DEFAULT_PATH)

message(STATUS "h ${LUA_LIBRARIES}, ${LUA_INCLUDE_DIR}" )

add_library(core SHARED libcore.h libcore.cpp)



target_link_libraries(core ${LUA_LIBRARIES})

# 设置包含目录，以便编译器可以找到 Lua 的头文件  
target_include_directories(core PRIVATE ${LUA_INCLUDE_DIR})

