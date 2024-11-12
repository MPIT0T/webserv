#ifndef LISTEN_HPP
#define LISTEN_HPP

#include <vector>
#include <string>
#include <map>

#include "Route.hpp"

class Listen
{
private:
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

	void setPort( int port );
	void setMaxBodySize( int maxBodySize );
	void setHost( std::string host );
	void setServerName( std::string serverName );
	void setErrorPages( std::map<int, std::string> errorPages );
	void setRoutes( std::vector<Route> routes );

	// Getters
	int getPort( void ) const;
	int getMaxBodySize( void ) const;
	std::string getHost( void ) const;
	std::string getServerName( void ) const;
	std::map<int, std::string> getErrorPages( void ) const;
	std::map<std::string, Route> getRoutes( void ) const;
};

#endif // Listen_HPP