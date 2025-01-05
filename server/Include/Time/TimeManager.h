#ifndef TIME_MANAGER
#define TIME_MANAGER

#include <mutex>
#include <iostream>



class TimeManager {

public:
    static TimeManager& GetInstance();

     TimeManager(){};

    time_t GetNowTime();
private:
	static TimeManager* instance;
	static std::once_flag initFlag;

    TimeManager(const TimeManager&) = delete;
    TimeManager& operator=(const TimeManager&) = delete;

	static void initSingleton();
};









int luaopen_libtime(lua_State *L);
int Luaopen_MakeTimeFunc(lua_State *L);

#endif
