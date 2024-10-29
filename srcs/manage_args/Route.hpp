#ifndef ROUTE_HPP
#define ROUTE_HPP

#include <string>
#include <map>

class Route{
private:
	bool								_directory_listing;
	std::string 						_path;
	std::string							_root;
	std::string 						_http_redirect;
	std::map <std::string, bool> 		_allow_methods;
	std::map <std::string, std::string> _cgi;

public:
	// Constructors
	Route( void );
	Route( const Route &src );
	Route &operator=( const Route &src );
	
	// Destructor
	~Route();
	
	// Setters

	// Getters
};

#endif // Route_HPP