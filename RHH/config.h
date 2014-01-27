#ifndef CONFIG_H
#define CONFIG_H

struct lua_State;

class Config
{
private:
	lua_State* lua;
public:
	Config(const char* file);
	~Config();
	bool GetBool(const char* variable_name);
	int GetInt(const char* variable_name);
	float GetFloat(const char* variable_name);
	double GetDouble(const char* variable_name);
	const char* GetString(const char* variable_name);
	static Config& Default();
};

#endif