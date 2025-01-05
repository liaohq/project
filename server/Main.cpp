#include<iostream>
#include "Libuv/Libuv.h"
#include "Core/Core.h"
#include "Lua/lua.hpp"
#include <unistd.h>
#include <thread>
#include <chrono>
#include <sstream>
#include "Time/TimeManager.h"
#include "TestLuaApi/TestLuaApi.h"
#include "Space/Space.h"

using namespace std;



static int mylib_add(lua_State *L) {
    double a = luaL_checknumber(L, 1);
    double b = luaL_checknumber(L, 2);
    lua_pushinteger(L, a + b);


    return 1;
};


static int NowTime(lua_State *L){
	lua_pushinteger(L, 1234);
	return 1;
}

static const struct luaL_Reg mylib_funcs[] = {
    {"add", mylib_add},
    {NULL, NULL}
};



int luaopen_libcore(lua_State *L) {
        luaL_newlib(L, mylib_funcs);
        lua_setglobal(L, "libcore");
        
		return 0;
}



int makeLuaCallFuncTest(lua_State *L){
	cout<<"makeLuaCallFuncTest"<<endl;

	lua_createtable(L, 0, 1);
	

	lua_pushstring(L, "add");
	lua_pushcfunction(L, mylib_add);
	lua_settable(L, -3);


	lua_pushstring(L, "GetNowTime");
	lua_pushcfunction(L, NowTime);
	lua_settable(L, -3);

	lua_setglobal(L, "clib_test");
}

int makeLuaCallFunc(lua_State *L){
	cout<<"makeLuaCallFunc"<<endl;
	lua_createtable(L, 0, 1);
	lua_setglobal(L, "clib");


	Luaopen_MakeTimeFunc(L);
}

char* GetExePath(){
	char *path = getcwd(NULL, 0);

	return path;
}

void setLuaSrcPath(lua_State *L){
	lua_getglobal(L, "package");
	lua_getfield(L, -1, "path");
	const char *path = lua_tostring(L, -1);
	//cout<<"old lua pachage.path:"<<path<<endl;

	char* curExePath = GetExePath();
	stringstream ss;
	ss<< path <<";"<<curExePath << "/../LuaSrc/?.lua";
	string newPath = ss.str();
	//cout<<"new lua pachage.path:"<<newPath<<endl;

	lua_pop(L, 1);
	lua_pushstring(L, newPath.c_str());
	lua_setfield(L, -2, "path");
}

void luaTest(){
	cout<<"luaTest begin"<<endl;
	lua_State* L = luaL_newstate();
	luaopen_base(L);
	luaL_openlibs(L);

	//lua_createtable(L, 0, 1);
	//lua_setglobal(L, "clib");

	luaopen_libtime(L);
	luaopen_libcore(L);
	luaopen_libtestluaapi(L);	
	
	lua_setglobal(L,"_script");	
	
	makeLuaCallFuncTest(L);
	makeLuaCallFunc(L);
	setLuaSrcPath(L);

	char* path = GetExePath();
	
	stringstream ss;
	ss<< path << "/../LuaSrc/Load.lua";


	string loadPath = ss.str();
	cout<<"Load.lua path:"<<loadPath<<endl;

	int ret = luaL_loadfile(L, loadPath.c_str());
	ret = lua_pcall(L, 0, 0, 0);
	if (ret != LUA_OK){
		cout<<"call lua fail, "<< lua_tostring(L, -1)<<endl;
	}

}

void startLibuv()
{
	Libuv libuv;
	libuv.Init();
}


void initSpace(){
	Space space(111);
	cout<<"space mapID:"<< space.GetMapID()<<endl;
}

int main(){
	//int result = add(1, 2);
	//cout<<"c++ call add result:"<<result<<endl;
	
	luaTest();
	initSpace();

	thread t1(startLibuv);
	t1.detach();	
	
	this_thread::sleep_for(chrono::seconds(1));
	string input;
	while(true){
		cout<<"enter cmd( input 'exit' quit process)"<<endl;
		getline(cin, input);
		if( input == "exit"){
			cout<<"exit process"<<endl;
			break;
		} else
		{
			cout<<"unknow cmd:"<<input<<endl;
		}
	}

	return 0;
}
