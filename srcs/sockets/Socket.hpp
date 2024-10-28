/* ***************** */
/*      WebServ      */
/* ***************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

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
	bool			create();
	bool			bind(const std::string &ip, int port) const;
	bool			listen() const;
	ClientInfo		*accept() const;
	static bool		send(ClientInfo *client, const std::string &data);
	static int		receive(ClientInfo *client);
	void			closeSocket();
	int 			getFd() const;

/* Exceptions */
	class SocketCreateException : public std::exception
	{
	public :
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

private:
	int		_fd;
};


#endif //SOCKET_HPP
