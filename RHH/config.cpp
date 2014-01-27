#include "config.h"
#include "lua.hpp"
#include <cassert>

#if _DEBUG
#pragma comment(lib, "Lua5.1.4-d.lib")
#else
#pragma comment(lib, "Lua5.1.lib")
#endif

Config& Config::Default()
{
	static Config config("./Resources/config.dat");
	return config;
}

Config::Config(const char* file)
{
	lua = lua_open();
	//luaL_openlibs(lua);
	if(luaL_loadfile(lua, file) || lua_pcall(lua, 0, 0, 0))
		assert(false && "Couldn't load config file");
}

Config::~Config()
{
	lua_close(lua);
}

bool Config::GetBool(const char* variable_name)
{
	lua_getglobal(lua, variable_name);
	if(!lua_isboolean(lua, -1))
		assert(false && "Couldn't load a boolean");

	if(lua_toboolean(lua, -1) != 0)
		return true;
	return false;
}

int Config::GetInt(const char* variable_name)
{
	lua_getglobal(lua, variable_name);
	if(!lua_isnumber(lua, -1))
		assert(false && "Couldn't load int");//variable_name + " isn't a boolean");

	return lua_tointeger(lua, -1);
}

float Config::GetFloat(const char* variable_name)
{
	lua_getglobal(lua, variable_name);
	if(!lua_isnumber(lua, -1))
		assert(false && "Couldn't load float");//variable_name + " isn't a boolean");

	return static_cast<float>(lua_tonumber(lua, -1));
}

double Config::GetDouble(const char* variable_name)
{
	lua_getglobal(lua, variable_name);
	if(!lua_isnumber(lua, -1))
		assert(false && "Couldn't load float");//variable_name + " isn't a boolean");

	return lua_tonumber(lua, -1);
}

const char* Config::GetString(const char* variable_name)
{
	lua_getglobal(lua, variable_name);
	if(!lua_isstring(lua, -1))
		assert(false && "Couldn't load int");//variable_name + " isn't a boolean");

	return lua_tostring(lua, -1);
}