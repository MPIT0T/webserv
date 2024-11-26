#ifndef CLIENTINFO_HPP
# define CLIENTINFO_HPP

#include <string>

class ClientInfo
{
public:
/* Constructors */
	ClientInfo();
	ClientInfo(int fd, int port, std::string ip, int listenID);
	ClientInfo(const ClientInfo &src);
	~ClientInfo();

/* Operators */
	ClientInfo &operator=(const ClientInfo &src);

/* Methods */
	int			fd() const;
	int			port() const;
	std::string	IP() const;
	int			listenID() const;

	void		setFD(int fd);
	void		setPort(int port);
	void		setIP(const std::string& ip);

private:
	int			_fd;
	int			_port;
	std::string	_ip;
	int			_listenID;
};



#endif //CLIENTINFO_HPP
