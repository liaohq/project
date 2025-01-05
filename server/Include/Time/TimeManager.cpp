#include "Lua/lua.hpp"
#include "TimeManager.h"


using namespace std;


TimeManager& TimeManager::GetInstance(){
	std::call_once(initFlag, &initSingleton);
}



void TimeManager::initSingleton(){
	cout<<"TimeManager initSingleton"<<endl;
	instance = new TimeManager;
}

time_t TimeManager::GetNowTime(){
	time_t nowTime;
	time(&nowTime);
	return nowTime;
}


std::once_flag TimeManager::initFlag;
TimeManager* TimeManager::instance = nullptr;











static int GetNowTime(lua_State *L){
        //TimeManager t;
		TimeManager& t = TimeManager::GetInstance();
        int nowTime = t.GetNowTime();

        lua_pushinteger(L, nowTime);
        return 1;
}

static int TestCallBackLuaFunc(lua_State *L){
	if(!lua_isinteger(L, 1) ){
		return luaL_error(L, "error by first argument to be an integer");
	}

	int args1 = lua_tointeger(L, 1);
	lua_pushinteger(L, args1);

	return 1;
}

static const luaL_Reg mylib_timeManager_funcs[] = {
        {"GetNowTime", GetNowTime},
        {NULL, NULL},
};




int luaopen_libtime(lua_State *L){
    cout<<"luaopen_libtime register func"<<endl;
    luaL_newlib(L, mylib_timeManager_funcs);
    lua_setglobal(L, "timeManager");
    
	return 1;
}


int Luaopen_MakeTimeFunc(lua_State *L){
	cout<<"Luaopen_MakeTimeFunc"<<endl;
	lua_getglobal(L, "clib");

	lua_pushstring(L, "GetNowTime");
	lua_pushcfunction(L, GetNowTime);
	lua_settable(L, -3);

	lua_pushstring(L, "TestCallBackLuaFunc");
	lua_pushcfunction(L, TestCallBackLuaFunc);
	lua_settable(L, -3);
}
