#include "LuaConfiguration.h"
#include "OgreLogManager.h"

LuaConfiguration::LuaConfiguration(const char *filename)
{
	m_lua = lua_open();
	luaL_openlibs(m_lua);

	try
	{
		int top = lua_gettop(m_lua);
		if(luaL_loadfile(m_lua, filename))
		{
			Ogre::LogManager::getSingleton().logMessage(Ogre::LML_NORMAL, "Couldn't load configuration file!");
		}
		else if(lua_pcall(m_lua, 0, 0, 0))
		{
			Ogre::LogManager::getSingleton().logMessage(Ogre::LML_NORMAL, lua_tostring(m_lua, lua_gettop(m_lua)));
			lua_pop(m_lua, 2);
		}
		lua_settop(m_lua, top);
	}
	catch(std::exception&)
	{
		lua_close(m_lua);
		throw;
	}
}

LuaConfiguration::~LuaConfiguration()
{
	lua_close(m_lua);
}

void LuaConfiguration::getBoolean(std::string name, bool& value)
{
	luaL_dostring(m_lua, std::string("return " + name).c_str());
	int top = lua_gettop(m_lua);
	if(!lua_isnil(m_lua, top))
		if(lua_isboolean(m_lua, top))
			value = lua_toboolean(m_lua, top);
		else
			Ogre::LogManager::getSingleton().logMessage(Ogre::LML_NORMAL, "Error in configuration file, "+name+" is not a boolean!");
	lua_pop(m_lua, 1);
}

void LuaConfiguration::getInteger(std::string name, int& value)
{
	luaL_dostring(m_lua, std::string("return " + name).c_str());
	int top = lua_gettop(m_lua);
	if(!lua_isnil(m_lua, top))
		if(lua_isnumber(m_lua, top))
			value = lua_tointeger(m_lua, top);
		else
			Ogre::LogManager::getSingleton().logMessage(Ogre::LML_NORMAL, "Error in configuration file, "+name+" is not a number!");
	lua_pop(m_lua, 1);
}

void LuaConfiguration::getFloat(std::string name, float& value)
{
	luaL_dostring(m_lua, std::string("return " + name).c_str());
	int top = lua_gettop(m_lua);
	if(!lua_isnil(m_lua, top))
		if(lua_isnumber(m_lua, top))
			value = lua_tonumber(m_lua, top);
		else
			Ogre::LogManager::getSingleton().logMessage(Ogre::LML_NORMAL, "Error in configuration file, "+name+" is not a number!");
	lua_pop(m_lua, 1);
}

void LuaConfiguration::getDouble(std::string name, double& value)
{
	luaL_dostring(m_lua, std::string("return " + name).c_str());
	int top = lua_gettop(m_lua);
	if(!lua_isnil(m_lua, top))
		if(lua_isnumber(m_lua, top))
			value = lua_tonumber(m_lua, top);
		else
			Ogre::LogManager::getSingleton().logMessage(Ogre::LML_NORMAL, "Error in configuration file, "+name+" is not a number!");
	lua_pop(m_lua, 1);
}

void LuaConfiguration::getString(std::string name, std::string& value)
{
	luaL_dostring(m_lua, std::string("return " + name).c_str());
	int top = lua_gettop(m_lua);
	if(!lua_isnil(m_lua, top))
		if(lua_isstring(m_lua, top))
			value = lua_tostring(m_lua, top);
		else
			Ogre::LogManager::getSingleton().logMessage(Ogre::LML_NORMAL, "Error in configuration file, "+name+" is not a string!");
	lua_pop(m_lua, 1);
}

void LuaConfiguration::getStringList(std::string name, std::vector<std::string>& list)
{
	luaL_dostring(m_lua, std::string("return " + name).c_str());
	int top = lua_gettop(m_lua);
	if(!lua_isnil(m_lua, top))
		if(lua_istable(m_lua, top))
		{
			lua_pushnil(m_lua);
			while(lua_next(m_lua, top))
			{
				if(lua_isstring(m_lua, -1))
				{
					list.push_back(lua_tostring(m_lua, -1));
					lua_pop(m_lua, 1);
				}
				else
					Ogre::LogManager::getSingleton().logMessage(Ogre::LML_NORMAL, "Error in configuration file, "+name+" contains a non-string member!");
			}
		}
		else
			Ogre::LogManager::getSingleton().logMessage(Ogre::LML_NORMAL, "Error in configuration file, "+name+" is not a list!");
	lua_pop(m_lua, 1);
}

void LuaConfiguration::getIndexList(std::string name, std::vector<std::string>& list)
{
	luaL_dostring(m_lua, std::string("return " + name).c_str());
	int top = lua_gettop(m_lua);
	if(!lua_isnil(m_lua, top))
		if(lua_istable(m_lua, top))
		{
			lua_pushnil(m_lua);
			while(lua_next(m_lua, top))
			{
				if(lua_isstring(m_lua, -2))
				{
					list.push_back(lua_tostring(m_lua, -2));
					lua_pop(m_lua, 1);
				}
				else
					Ogre::LogManager::getSingleton().logMessage(Ogre::LML_NORMAL, "Error in configuration file, "+name+" contains a non-string member!");
			}
		}
		else
			Ogre::LogManager::getSingleton().logMessage(Ogre::LML_NORMAL, "Error in configuration file, "+name+" is not a list!");
	lua_pop(m_lua, 1);
}

void LuaConfiguration::getIndexStringList(std::string name, std::vector<std::pair<std::string, std::string> >& list)
{
	luaL_dostring(m_lua, std::string("return " + name).c_str());
	int top = lua_gettop(m_lua);
	if(!lua_isnil(m_lua, top))
		if(lua_istable(m_lua, top))
		{
			lua_pushnil(m_lua);
			while(lua_next(m_lua, top))
			{
				if(lua_isstring(m_lua, -1) && lua_isstring(m_lua, -2))
				{
					list.push_back(std::pair<std::string, std::string>(lua_tostring(m_lua, -2), lua_tostring(m_lua, -1)));
					lua_pop(m_lua, 1);
				}
				else
					Ogre::LogManager::getSingleton().logMessage(Ogre::LML_NORMAL, "Error in configuration file, "+name+" contains a non-string member!");
			}
		}
		else
			Ogre::LogManager::getSingleton().logMessage(Ogre::LML_NORMAL, "Error in configuration file, "+name+" is not a list!");
	lua_pop(m_lua, 1);
}
