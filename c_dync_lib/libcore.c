//#include <lua.hpp>
  #include <lua.h>  
  #include <lauxlib.h>  
  #include <lualib.h> 

static int my_function(lua_State *L) {  
    // 从 Lua 栈中获取参数  
    int arg = luaL_checkinteger(L, 1);  
      
    // 执行一些操作，例如将参数加倍  
    int result = arg * 2;  
      
    // 将结果推回 Lua 栈  
    lua_pushinteger(L, result);  
      
    // 返回结果的数量（在这种情况下为 1）  
    return 1;  
}  
  
// 创建一个表来存储你的函数  
static const struct luaL_Reg mylib[] = {  
    {"my_function", my_function},  
    {NULL, NULL}  
};  
  
// Lua 加载库的函数  
int luaopen_libcore(lua_State *L) {  
    luaL_newlib(L, mylib);  
    return 1;  
}
