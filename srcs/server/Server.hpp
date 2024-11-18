/* ***************** */
/*      WebServ      */
/* ***************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include "Socket.hpp"
# include <unistd.h>
# include <fstream>
#include <cstdlib>
#include <Signal.hpp>
#include <vector>
#include "Listen.hpp"
class Server
{
private:
	Socket				_socket;
	std::vector<Listen>	_listen;
	Signal				_signals;

/* private method */
	std::vector<Listen>	setListen(std::string content);
	std::string			trimConfig(const std::string& content);
	void				checkJsonFormat(const std::string &content);

public:
	Server( void );
	Server( const Server &src );
	Server &operator=( const Server &src );

	~Server();


	void init( void );
	void run( void );
	void stop( void );
	bool				parseConfigFile( std::string configFile );


	class ServerConfigJSONFormatException : public std::exception
	{
		const char *what() const throw();
	};
};

#endif // Server_HPP