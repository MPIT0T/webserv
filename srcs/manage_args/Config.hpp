#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <iostream>
#include <fstream>

class Config{
private:
	

public:
	Config( void );
	Config( const Config &src );
	Config &operator=( const Config &src );
	
	~Config();

	void parseConfigFile( std::string configFile );

	
};

#endif // CONFIG_HPP