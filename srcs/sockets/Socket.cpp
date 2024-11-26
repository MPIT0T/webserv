/* ***************** */
/*      WebServ      */
/* ***************** */

#include "Socket.hpp"
#include "colors.h"
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

#include <fcntl.h>
/* Methods ****************************************************************** */
void Socket::create()
{
	int one = 1;
	_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_fd < 0)		// if socket failed
		throw SocketCreateException();
	if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int)) == -1)
		throw SocketCreateException(); //TODO create socket option exception
}

void Socket::bind(const std::string &ip, const int port) const
{
	sockaddr_in	addr = {};

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip.c_str());
	addr.sin_port = htons(port);

	if (::bind(_fd, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) == -1)
		throw SocketBindException();
}

void Socket::listen() const
{
	if (::listen(_fd, 5) < 0)
		throw SocketListenException();
}

ClientInfo *Socket::accept() const
{
	sockaddr_in clientAddr = {};
	socklen_t	clientLen = sizeof(clientAddr);
	int			clientFD = ::accept(_fd, reinterpret_cast<struct sockaddr*>(&clientAddr), &clientLen);
	std::string	clientIP;
	int			clientPort;

	if (clientFD < 0)
		throw SocketAcceptException();

	clientIP = inet_ntoa(clientAddr.sin_addr);
	clientPort = ntohs(clientAddr.sin_port);

	return (new ClientInfo(clientFD, clientPort, clientIP));
}

bool Socket::send(ClientInfo *client, const std::string &data)
{
	return (write(client->fd(), data.c_str(), data.size()) != -1);
}

Request *Socket::receive(ClientInfo *client)
{
	const ssize_t	tmp_size = 2048;
	char			tmp[tmp_size];
	ssize_t			len = 0;
	size_t			lenTotal = 0;
	std::string		buffer = "";
	Request			*request = new Request();


	while (42)
	{
		len = recv(client->fd(), tmp, tmp_size, 0);
		if (len < 0)
		{
			delete request;
			throw SocketReceiveException();
		}

		if (len == 0)
			break ;

		buffer.append(tmp);
		lenTotal += len;

		if (len < tmp_size)
			break ;
	}
	request->setRequest(buffer);
	return (request);
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

const char *Socket::SocketListenException::what() const throw()
{
	return ("Can't listen to socket.");
}

const char* Socket::SocketAcceptException::what() const throw()
{
	return ("Can't accept client.");
}

const char* Socket::SocketSendException::what() const throw()
{
	return ("Error sending packet.");
}

const char* Socket::SocketReceiveException::what() const throw()
{
	return ("Error receiving packet.");
}

