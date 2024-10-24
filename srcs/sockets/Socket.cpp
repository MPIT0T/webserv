/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:33:04 by mpitot            #+#    #+#             */
/*   Updated: 2024/10/24 11:12:49 by mbrousse         ###   ########.fr       */
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
	struct sockaddr_in addr;
	
	(void)ip;
	addr.sin_family = AF_INET;
	// addr.sin_addr.s_addr = inet_addr(ip.c_str());
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	printf("http://%s:%i\n", inet_ntoa(addr.sin_addr), port);
	// printf("http://%s:%i\n", ip.c_str(), port);

	if (::bind(_fd, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
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

int Socket::accept() const
{
	struct sockaddr_in cli_addr;
	socklen_t client_len = sizeof(cli_addr);
	int client_fd = ::accept(_fd, (struct sockaddr *) &cli_addr, &client_len);
	return client_fd;
}

bool Socket::send(const int clientSock, const std::string &data)
{
	return (write(clientSock, data.c_str(), data.size() ) != -1);
}

int Socket::receive(int client_sock, char* buffer, const size_t bufferSize)
{
	return (read(client_sock, buffer, bufferSize));
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

