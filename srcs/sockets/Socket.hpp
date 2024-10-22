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

private:
	int		_fd;
};



#endif //SOCKET_HPP
