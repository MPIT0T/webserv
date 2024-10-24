/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:52:23 by mpitot            #+#    #+#             */
/*   Updated: 2024/10/24 11:12:53 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

# include <string>
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
	int				accept() const;
	static bool		send(int clientSock, const std::string &data);
	static int		receive(int clientSock, char *buffer, size_t bufferSize);
	void			closeSocket();
	int 			getFd() const;

	
private:
	int		_fd;
};



#endif //SOCKET_HPP
