/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:33:04 by mpitot            #+#    #+#             */
/*   Updated: 2024/10/22 14:09:56 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

#include <functional>

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
		err(1, "can't open socket");
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
		close(_fd);
		err(1, "Can't bind");
		return (false);
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
	socklen_t clientLen = sizeof(clientAddr);
	const int clientSock = ::accept(_fd, reinterpret_cast<struct sockaddr*>(&clientAddr), &clientLen);
	if (clientSock == -1)
		return (NULL);
	std::string clientIP = inet_ntoa(clientAddr.sin_addr);
	int			clientPort = ntohs(clientAddr.sin_port);

	return new ClientInfo(clientSock, clientPort, clientIP);
}

bool Socket::send(const int clientSock, const std::string &data)
{
	return (write(clientSock, data.c_str(), data.size() ) != -1);
}

int Socket::receive(int client_sock)
{
	char buffer[2048];
	int len = recv(client_sock, buffer, 2048, 0);
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
	return _fd;
}

