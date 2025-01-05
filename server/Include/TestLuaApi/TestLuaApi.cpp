#include "Lua/lua.hpp"
#include "TestLuaApi.h"

using namespace std;

void TestLuaApi::Test(){
	cout<<"TestLuaApi Test"<<endl;
}


static int TestInteger(lua_State *L){
	if(!lua_isinteger(L, 1) ){
		//return luaL_error(L, "error by first argument is not int");
		return luaL_argerror(L, -1, "error by first argument is not int");
	}

	int arg1 = lua_tointeger(L, 1);

	lua_pushinteger(L, arg1);
	return 1;
}

static int TestFuncCallback(lua_State *L){
	int arg1 = luaL_checkinteger(L, 1);
	int arg2 = luaL_checkinteger(L, 2);

	if(!lua_isfunction(L, 3)){
		return luaL_argerror(L, 3, "not function");
	}

	lua_pushvalue(L, 3);
	lua_pushinteger(L, arg1);
	lua_pushinteger(L, arg2);

	if(lua_pcall(L, 2, 0, 0) != LUA_OK){
		const char *err = lua_tostring(L, -1);
		cout<<"call lua err:"<<err<<endl;
		//lua_pop(L, 1);
		return 1;
	}

	lua_pushboolean(L, 1);
	return 1;
}

static const luaL_Reg testLuaApiFunc[] = {
	{"TestInteger", TestInteger},
	{"TestFuncCallback", TestFuncCallback},
	{NULL, NULL},
};

int luaopen_libtestluaapi(lua_State *L){
	cout<<"handle libtestluaapi"<<endl;
	luaL_newlib(L, testLuaApiFunc);
	lua_setglobal(L, "TestLuaApi");

	return 1;
}
