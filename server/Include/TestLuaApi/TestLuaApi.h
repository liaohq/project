#ifndef TEST_LUA_API
#define TEST_LUA_API
#include<iostream>

class TestLuaApi{
	public:
		void Test();
	private:
};



int luaopen_libtestluaapi(lua_State *L);

#endif
