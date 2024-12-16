#ifndef CLIENTINFO_HPP
# define CLIENTINFO_HPP

#include <string>
#include <unistd.h>
#include <iostream>
#include <map>
#include "Route.hpp"
#include "Socket.hpp"

class Socket;

class Route;

class ClientInfo
{
private:
	int			_fd;
	int			_port;
	std::string	_ip;
	std::string	_routeAccess;
	int			_listenID;
public:
/* Constructors */
	ClientInfo();
	ClientInfo(int fd, int port, std::string ip, int listenID);
	ClientInfo(const ClientInfo &src);
	~ClientInfo();

/* Operators */
	ClientInfo &operator=(const ClientInfo &src);

/* Methods */
	int			fd() const;
	int			port() const;
	std::string	IP() const;
	int			listenID() const;

	void		setFD(int fd);
	void		setPort(int port);
	void		setIP(const std::string& ip);
	void		setRouteAccess(const std::string& routeAccess , const std::map<std::string, Route> &routes);

	std::string	getRouteAccess() const;

};



#endif //CLIENTINFO_HPP
