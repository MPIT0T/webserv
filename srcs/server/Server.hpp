/* ***************** */
/*      WebServ      */
/* ***************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <unistd.h>
#include <sys/poll.h>
#include <sys/epoll.h>
#include <vector>
#include <stack>
#include <algorithm>
#include <map>
#include <err.h>
#include <fstream>
#include <cstdlib>
#include <csignal>

#include "Logger.hpp"
#include "Listen.hpp"
#include "Request.hpp"
#include "Socket.hpp"
#include "utils.hpp"

class Signal;

class Server
{
private:
	std::vector<Listen>	_listens;
	char				**_env;
	std::map<int, ClientInfo *> clients;

/* private method */
	std::vector<Listen>	setListen(std::string content);
	std::string			trimConfig(const std::string& content);
	void				checkJsonFormat(const std::string &content);

public:
	Logger				log;
	static bool			_signals;
	Server( void );
	Server( const Server &src );
	Server &operator=( const Server &src );

	~Server();


	void init( void );
	void run( void );
	void stop( void );
	bool				parseConfigFile( std::string configFile );
	void				setEnv(char **env);
	char				**getEnv(void);


	class ServerConfigJSONFormatException : public std::exception
	{
		const char *what() const throw();
	};

	static void	handleSIGINT(int sig);
};

#endif // Server_HPP