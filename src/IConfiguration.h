#ifndef ICONFIGURATION_H
#define ICONFIGURATION_H

#include <string>
#include <vector>

class IConfiguration
{
public:
	virtual void getBoolean(std::string name, bool& value)=0;
	virtual void getInteger(std::string name, int& value)=0;
	virtual void getFloat(std::string name, float& value)=0;
	virtual void getDouble(std::string name, double& value)=0;
	virtual void getString(std::string name, std::string& value)=0;
	virtual void getStringList(std::string name, std::vector<std::string>& list)=0;
	virtual void getIndexList(std::string name, std::vector<std::string>& list)=0;
	virtual void getIndexStringList(std::string name, std::vector<std::pair<std::string, std::string> >& list)=0;
};

#endif // ICONFIGURATION_H
