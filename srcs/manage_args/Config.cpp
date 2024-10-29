#include "Config.hpp"

Config::Config( void )
{
	return ;
}

Config::Config( const Config &src )
{
	*this = src;
	return ;
}

Config &Config::operator=( const Config &src )
{
	if (this != &src)
	{
	}
	return *this;
}

Config::~Config()
{
	return ;
}

void Config::parseConfigFile( std::string configFile )
{
	std::ifstream file(configFile);
	std::string line;
	std::string key;
	std::string value;

	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			if (line[0] == '#')
				continue;
			key = line.substr(0, line.find(":"));
			value = line.substr(line.find(":") + 1);
			std::cout << key << " : " << value << std::endl;
		}
		file.close();
	}
	else
		throw std::exception();
	return ;
}