#include "libcore.h"
#include <lua.hpp>
/*
#include <lua.h>  
#include <lauxlib.h>  
#include <lualib.h> 
*/
#pragma pack(8)
#include<iostream>
using namespace std;


class A {
public:
	int a;
};

class B: virtual public A{
	int b;
};

class C: virtual public A{
	int c;
};

class D: public B, public C{
	int d;
};
static int test(lua_State *L){
	A  a;
	B  b;
	C  c;
	D  d;

	d.B::a = 1;
	cout<<"d.C::a:"<<d.C::a<<endl;
	
	cout<<"* size:"<<sizeof(void*)<<endl;
	cout<<"a size:"<<sizeof(a)<<", "<<&a <<endl;
	cout<<"b size:"<<sizeof(b)<<", "<<&b<<endl;
	cout<<"c size:"<<sizeof(c)<<", "<<&c <<endl;
	cout<<"d size:"<<sizeof(d)<<", "<<&d <<endl;

	cout<<"************"<<endl;

	cout<<"d.a addr " <<&d.a <<endl;
	cout<<"d.B::a addr " <<&d.B::a <<endl;
	cout<<"d.C::a addr " <<&d.C::a <<endl;

	return 0;
}

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
    {"test", test},  
};  
  
// Lua 加载库的函数  
int luaopen_libcore(lua_State *L) {  
    luaL_newlib(L, mylib);  
    return 1;  
}
