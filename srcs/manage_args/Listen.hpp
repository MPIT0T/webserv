#ifndef LISTEN_HPP
#define LISTEN_HPP

#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include <Socket.hpp>
#include "Route.hpp"

class Socket;

class Listen
{
private:
	Socket							_socket;
	int 							_port;
	int 							_maxBodySize;
	std::string 					_host;
	std::string 					_serverName;
	std::map<int, std::string> 		_errorPages;
	
	std::map<std::string, Route> 	_routes;

public:
	// Constructors
	
	Listen( void );
	Listen(std::string content);
	Listen( const Listen &src );
	Listen &operator=( const Listen &src );
	
	// Destructor

	~Listen();

	// Setters

	void		setSocket(const std::string& hostName, int port);
	void 		setPort( int port );
	void 		setMaxBodySize( int maxBodySize );
	void		setHost( std::string host );
	void		setServerName( std::string serverName );
	void		setErrorPages( std::map<int, std::string> errorPages );
	void		setRoutes( std::vector<Route> routes );


	// Getters
	Socket							&getSocket();
	int								getPort( void ) const;
	int								getMaxBodySize( void ) const;
	std::string						getHost( void ) const;
	std::string						getServerName( void ) const;
	std::map<int, std::string>		getErrorPages( void ) const;
	std::map<std::string, Route>	getRoutes( void ) const;

	//parsing
	void 	parseRoutes(const std::string &routesStr);
	void	parseErrorPages(const std::string &errorPagesStr );
	int 	parseSize(const std::string &sizeStr);

};

#endif // Listen_HPP