#ifndef LUACONFIGURATION_H
#define LUACONFIGURATION_H

#include <string>
#include <vector>
#include <lua.hpp>

#include "IConfiguration.h"

class LuaConfiguration : public IConfiguration
{
private:
	lua_State* m_lua;
public:
	LuaConfiguration(const char* filename);
	virtual ~LuaConfiguration();

	virtual void getBoolean(std::string name, bool& value);
	virtual void getInteger(std::string name, int& value);
	virtual void getFloat(std::string name, float& value);
	virtual void getDouble(std::string name, double& value);
	virtual void getString(std::string name, std::string& value);
	virtual void getStringList(std::string name, std::vector<std::string>& list);
	virtual void getIndexList(std::string name, std::vector<std::string>& list);
	virtual void getIndexStringList(std::string name, std::vector<std::pair<std::string, std::string>>& list);
};

#endif // LUACONFIGURATION_H
