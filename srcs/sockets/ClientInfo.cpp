/* ***************** */
/*      WebServ      */
/* ***************** */

#include "ClientInfo.hpp"
#include <unistd.h>

/* Constructors ************************************************************* */
ClientInfo::ClientInfo() {}

ClientInfo::ClientInfo(int fd, int port, std::string ip, int listenID)
{
	_fd = fd;
	_port = port;
	_ip = ip;
	_listenID = listenID;
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

int ClientInfo::listenID() const
{
	return (_listenID);
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
