#include "Listen.hpp"

// Constructors
Listen::Listen(void) : _port(0), _maxBodySize(0), _host(""), _serverName("") {}

Listen::Listen(const Listen &src) {
	*this = src;
}

Listen &Listen::operator=(const Listen &src) {
	if (this != &src) {
		this->_port = src._port;
		this->_maxBodySize = src._maxBodySize;
		this->_host = src._host;
		this->_serverName = src._serverName;
		this->_errorPages = src._errorPages;
		this->_routes = src._routes;
	}
	return *this;
}

// Destructor
Listen::~Listen() {}

// Setters
void Listen::setPort(int port) {
	_port = port;
}

void Listen::setMaxBodySize(int maxBodySize) {
	_maxBodySize = maxBodySize;
}

void Listen::setHost(std::string host) {
	_host = host;
}

void Listen::setServerName(std::string serverName) {
	_serverName = serverName;
}

void Listen::setErrorPages(std::map<int, std::string> errorPages) {
	_errorPages = errorPages;
}

void Listen::setRoutes(std::vector<Route> routes) {
	_routes.clear();
	for (size_t i = 0; i < routes.size(); ++i) {
		_routes[routes[i].getPath()] = routes[i];
	}
}

// Getters
int Listen::getPort(void) const {
	return _port;
}

int Listen::getMaxBodySize(void) const {
	return _maxBodySize;
}

std::string Listen::getHost(void) const {
	return _host;
}

std::string Listen::getServerName(void) const {
	return _serverName;
}



#ifndef CLASS_NAME_HPP
#define CLASS_NAME_HPP

class CLASS_NAME{
private:
	
public:
	CLASS_NAME( void );
	CLASS_NAME( const CLASS_NAME &src );
	CLASS_NAME &operator=( const CLASS_NAME &src );
	
	~CLASS_NAME();
	
};

#endif // CLASS_NAME_HPP