/* ***************** */
/*      WebServ      */
/* ***************** */

#include "ClientInfo.hpp"


/* Constructors ************************************************************* */
ClientInfo::ClientInfo() {}

ClientInfo::ClientInfo(int fd, int port, std::string ip)
{
	_fd = fd;
	_port = port;
	_ip = ip;
	_routeAccess = "/";
}

ClientInfo::ClientInfo(const ClientInfo &src)
{
	*this = src;
}

ClientInfo::~ClientInfo()
{
	close(_fd);
}

/* Operators **************************************************************** */
ClientInfo &ClientInfo::operator=(const ClientInfo &src)
{
	_fd = src.fd();
	_port = src.port();
	_ip = src.IP();
	return (*this);
}

/* Methods ****************************************************************** */
int ClientInfo::fd() const
{
	return (_fd);
}

int ClientInfo::port() const
{
	return (_port);
}

std::string ClientInfo::IP() const
{
	return (_ip);
}

void ClientInfo::setFD(const int fd)
{
	_fd = fd;
}

void ClientInfo::setPort(const int port)
{
	_port = port;
}

void ClientInfo::setIP(const std::string &ip)
{
	_ip = ip;
}

void ClientInfo::setRouteAccess(const std::string &routeAccess, const std::map<std::string, Route> &routes)
{
	for (std::map<std::string, Route>::const_iterator it = routes.begin(); it != routes.end(); ++it)
	{
		if (routeAccess == it->first)
		{
			_routeAccess = it->second.getRoot();
			return ;
		}
	}
}

std::string ClientInfo::getRouteAccess()
{
	return (_routeAccess);
}