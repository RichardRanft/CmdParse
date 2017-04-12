#include "Parser.h"

CParser::CParser()
{
	m_state = "";
}

CParser::CParser(std::map<std::string, std::pair<EArgType, bool>> argList)
{
	m_state = "";
	m_argRequired = argList;
	for (std::map<std::string, std::pair<EArgType, bool>>::const_iterator itr = m_argRequired.begin(); itr != m_argRequired.end(); itr++)
	{
		if ((*itr).second.first == EArgType::FLAG)
		{
			std::string val = "false";
			std::pair<std::string, std::string> pair = std::pair<std::string, std::string>((*itr).first, val);
			m_argDictTemp.insert(pair);
		}
		else
		{
			std::string empty = "";
			std::pair<std::string, std::string> pair = std::pair<std::string, std::string>((*itr).first, empty);
			m_argDictTemp.insert(pair);
		}
	}
}

bool CParser::Parse(std::list<std::string> args)
{
	for (std::list<std::string>::const_iterator itr = args.begin(); itr != args.end(); itr++)
	{
		std::map <std::string, std::string>::iterator it = m_argDictTemp.find((*itr));
		if (it != m_argDictTemp.end())
		{
			m_state = (*itr);
			if (m_argRequired[(*it).first].first == EArgType::FLAG)
			{
				m_argDictTemp[m_state] = "true";
				m_state = "";
			}
		}
		else
		{
			m_argDictTemp[m_state] = (*itr);
			m_state = "";
		}
	}
	for (std::map<std::string, std::string>::const_iterator itr = m_argDictTemp.begin(); itr != m_argDictTemp.end(); itr++)
	{
		if (m_argRequired[(*itr).first].second && m_argDictTemp[(*itr).first].empty())
			return false;
	}
	for (std::map<std::string, std::string>::const_iterator itr = m_argDictTemp.begin(); itr != m_argDictTemp.end(); itr++)
	{
		const std::string first = std::string((*itr).first);
		const std::string second = std::string((*itr).second);
		std::pair<const std::string, const std::string> temp = std::pair<const std::string, const std::string>(first, second);
		m_argDictionary.insert(temp);
	}
	return true;
}

const std::map<const std::string, const std::string>& CParser::GetOptions() const
{
	return m_argDictionary;
}

CParser::~CParser()
{
}
