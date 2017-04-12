#pragma once
#include <map>
#include <list>
#include <utility>
#include <string>

enum EArgType
{
	FLAG,
	VALUE
}; 

class CParser
{
private:
	std::map<std::string, std::pair<EArgType, bool>> m_argRequired;
	std::map<const std::string, const std::string> m_argDictionary;
	std::map<std::string, std::string> m_argDictTemp;
	std::string m_state;

public:
	CParser();
	CParser(std::map<std::string, std::pair<EArgType, bool>>);
	~CParser();

	bool Parse(std::list<std::string>);
	const std::map<const std::string, const std::string>& GetOptions() const;
};
