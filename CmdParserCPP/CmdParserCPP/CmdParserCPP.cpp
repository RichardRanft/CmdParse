// CmdParserCPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Parser.h"
#include <iostream>
#include <utility>

void usage()
{
	std::cout << "-p path      required" << std::endl;
	std::cout << "-u user      required" << std::endl;
	std::cout << "-v version   optional" << std::endl;
	std::cout << "-o overwrite optional" << std::endl;
}

int main(int argc, char* argv[])
{
	std::map<std::string, std::pair<EArgType, bool>> argdefs;
	std::string path = "-p";
	std::string user = "-u";
	std::string vers = "-v";
	std::string over = "-o";
	argdefs.insert(std::pair<std::string, std::pair<EArgType, bool>>(path, std::pair<EArgType, bool >(EArgType::VALUE, true)));
	argdefs.insert(std::pair<std::string, std::pair<EArgType, bool>>(user, std::pair<EArgType, bool>(EArgType::VALUE, true)));
	argdefs.insert(std::pair<std::string, std::pair<EArgType, bool>>(vers, std::pair<EArgType, bool>(EArgType::VALUE, false)));
	argdefs.insert(std::pair<std::string, std::pair<EArgType, bool>>(over, std::pair<EArgType, bool>(EArgType::FLAG, false)));

	CParser parser(argdefs);
	std::list<std::string> arglist;
	for (int i = 1; i < argc; i++)
	{
		arglist.push_back(argv[i]);
	}
	bool parsed = parser.Parse(arglist);

	std::map<std::string, std::string> opts = parser.GetOptions();

	std::cout << path << " = " << opts[path] << std::endl;
	std::cout << user << " = " << opts[user] << std::endl;
	std::cout << vers << " = " << opts[vers] << std::endl;
	std::cout << over << " = " << opts[over] << std::endl;
	if (!parsed)
		usage();
	return 0;
}
