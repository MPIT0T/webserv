/* ***************** */
/*      WebServ      */
/* ***************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

#include <Request.hpp>
# include <string>
# include <stdexcept>
# include "ClientInfo.hpp"

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
	void			create();
	void			bind(const std::string &ip, int port) const;
	void			listen() const;
	ClientInfo		*accept(int listenID) const;
	static bool		send(ClientInfo *client, const std::string &data);
	Request			*receive(ClientInfo *client);
	void			closeSocket();
	int 			getFd() const;

/* Exceptions */
	class SocketCreateException : public std::exception
	{
	public :
		const char *what() const throw();
	};

	class SocketOptionSetException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class SocketBindException : public std::exception
	{
	public :
		const char *what() const throw();
	};

	class SocketListenException : public std::exception
	{
	public :
		const char *what() const throw();
	};

	class SocketAcceptException : public std::exception
	{
	public :
		const char *what() const throw();
	};

	class SocketSendException : public std::exception
	{
	public :
		const char *what() const throw();
	};

	class SocketReceiveException : public std::exception
	{
	public :
		const char *what() const throw();
	};

private:
	int		_fd;
};


#endif //SOCKET_HPP
