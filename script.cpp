#include "script.h"

#include <stdlib.h>
#include <stdio.h>

Script::Script(const char* path) {
     lua_State* L = luaL_newstate();
     luaL_openlibs(L);
     if(luaL_loadfile(L, path) || lua_pcall(L,0,0,0))
         printf("%s\n", lua_tostring(L, -1));
     this->L = L;
 }
 
 Script::~Script() {
     lua_close(L);
 }   
 
 double Script::getNumber(const char* var_name) {
     lua_getglobal(L, var_name);
     if(!lua_isnumber(L, -1))
         printf("%s is not a number\n", var_name);
     double value = lua_tonumber(L,-1);
     lua_remove(L,-1);
     return value;
 }   
 
 bool Script::getBoolean(const char* var_name) {
     lua_getglobal(L, var_name);
     if(!lua_isboolean(L, -1))
         printf("%s is not a boolean\n", var_name);
     int value = lua_toboolean(L, -1);
     lua_remove(L, -1);
     return value == 1 ? true : false;
}