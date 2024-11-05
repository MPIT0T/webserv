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
#include <vector>
#include "Listen.hpp"
class Server
{
private:
	Socket _socket;

	std::vector<Listen> _listen;
	std::vector<Listen> setListen(std::vector<std::string> tokens);

	
public:
	Server( void );
	Server( const Server &src );
	Server &operator=( const Server &src );

	~Server();


	bool	parseConfigFile( std::string configFile );
	int		checkContentErrors
	void	init( void );
	void	run( void );
	void	stop( void );
};

#endif // Server_HPP