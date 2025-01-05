#include<iostream>
#include "Core.h"
#include "Lua/lua.hpp" 
#include "Base/Time/TimeManager.h"


using namespace std;



int add(int a, int b){
	return a+b;

}



static TimeManager* tmInst  = new TimeManager();

static int mylib_getTime(lua_State *L) { 

	TimeManager tm;
	int t = tm.GetNowTime();
	
	lua_pushinteger(L, t);
	return 1;
}


static int mylib_add(lua_State *L) {  
    double a = luaL_checknumber(L, 1);  
    double b = luaL_checknumber(L, 2);  
    lua_pushinteger(L, a + b);  

	
	return 1;  
};  

static int mylib_getMicroSeconds(lua_State *L){
	TimeManager tm;
	uint64_t microSeconds = tm.GetMicroSeconds();
	cout<<"microSeconds:"<<microSeconds<<endl;
	lua_pushinteger(L,static_cast<lua_Integer>(microSeconds));
	return 1;
}
  
static const struct luaL_Reg mylib_funcs[] = {  
    {"add", mylib_add},  
    {"getTime", mylib_getTime},  
    {"getMicroSeconds", mylib_getMicroSeconds},  
    {NULL, NULL}  
};  


extern "C" {

int luaopen_libcore(lua_State *L) {  
	cout<<"luaopen_libcore"<<endl;
	luaL_newlib(L, mylib_funcs);  
	lua_setglobal(L, "mylib");

	lua_getglobal(L, "clib");
    int top_idx = lua_gettop(L);	
	cout<<"top_idx:"<<top_idx<<endl;
	lua_pushstring(L, "test");
	lua_pushcfunction(L, mylib_getTime);
	lua_settable(L, -3);
	return 1;  
}

}

