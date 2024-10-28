/* ***************** */
/*      WebServ      */
/* ***************** */

#include "Socket.hpp"
#include <err.h>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>

/* Constructors ************************************************************* */
Socket::Socket()
{
	_fd = -1;
}

Socket::Socket(const Socket &src)
{
	*this = src;
}

Socket::~Socket()
{
	if (_fd != -1)
		close(_fd);
}

/* Operators **************************************************************** */
Socket &Socket::operator=(const Socket &src)
{
	_fd = src._fd;
	return (*this);
}

/* Methods ****************************************************************** */
bool Socket::create()
{
	int one = 1;
	_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_fd < 0)		// if socket failed
	{
		return (false);
	}
	setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));
	return (true);
}

bool Socket::bind(const std::string &ip, const int port) const
{
	sockaddr_in	addr = {};

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip.c_str());
	addr.sin_port = htons(port);

	if (::bind(_fd, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) == -1)
	{

	}
	return (true);
}

bool Socket::listen() const
{
	return ::listen(_fd, 5) != -1;
}

ClientInfo *Socket::accept() const
{
	sockaddr_in clientAddr = {};
	socklen_t	clientLen = sizeof(clientAddr);
	int			clientFD = ::accept(_fd, reinterpret_cast<struct sockaddr*>(&clientAddr), &clientLen);
	std::string	clientIP;
	int			clientPort;

	if (clientFD < 0)
		return (NULL);

	clientIP = inet_ntoa(clientAddr.sin_addr);
	clientPort = ntohs(clientAddr.sin_port);

	return (new ClientInfo(clientFD, clientPort, clientIP));
}

bool Socket::send(ClientInfo *client, const std::string &data)
{
	int		clientFD = reinterpret_cast<int>(client->fd());

	return (write(clientFD, data.c_str(), data.size() ) != -1);
}

int Socket::receive(ClientInfo *client)
{
	char buffer[2048];
	int len = recv(client->fd(), buffer, 2048, 0);
	buffer[len] = 0;
	printf("%s\n", buffer);
	return (0);
}

void Socket::closeSocket()
{
	if (_fd != -1)
	{
		close(_fd);
		_fd = -1;
	}
}

int Socket::getFd() const
{
	return (_fd);
}

/* Exceptions *************************************************************** */
const char *Socket::SocketCreateException::what() const throw()
{
	return ("Can't create socket.");
}

const char* Socket::SocketBindException::what() const throw()
{
	return ("Can't bind socket to port.");
}

const char* Socket::SocketListenException::what() const throw()
{
	return ("Can't listen to socket.");
}
