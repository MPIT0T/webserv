/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:52:23 by mpitot            #+#    #+#             */
/*   Updated: 2024/10/22 13:05:20 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

# include <string>
# include "ClientInfo.hpp"
#include <cstdio>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <err.h>

class Socket
{
public:
/* Constructors */
	Socket();
	Socket(const Socket &src);
	~Socket();

/* Operators */
	Socket &operator=(const Socket &src);

/* Methods */
	bool			create();
	bool			bind(const std::string &ip, int port) const;
	bool			listen() const;
	ClientInfo		*accept() const;
	static bool		send(int clientSock, const std::string &data);
	static int		receive(int clientSock);
	void			closeSocket();
	int 			getFd() const;


private:
	int		_fd;
};



#endif //SOCKET_HPP
