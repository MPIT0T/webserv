/* ***************** */
/*      WebServ      */
/* ***************** */

#include "Server.hpp"
#include "Request.hpp"
#include "SendResponse.hpp"
#include <err.h>
#include <map>

Server::Server( void )
{
	return ;
}

Server::Server( const Server &src )
{
	*this = src;
	return ;
}

Server &Server::operator=( const Server &src )
{
	if (this != &src)
	{
	}
	return *this;
}

Server::~Server()
{
	return ;
}

void Server::init(void)
{
	_socket.create();
	_socket.bind("127.0.0.1", 4242);
	_socket.listen();
}

void Server::run(void)
{
	ClientInfo		*client;
	Request			*request;
	SendResponse	*response;

	std::cout << "Waiting for connection..." << std::endl << std::endl;

	while (42)
	{
		try {
			client = _socket.accept();
			std::cout << "Client connected." << std::endl << std::endl;
			request = _socket.receive(client);
			response = new SendResponse("HTTP/1.1", "keep-alive","webServ", "text/html", "www/main/index.html", OK);
			_socket.send(client, response->getMessage());
			delete request;
			delete client;
			delete response;
		}
		catch (Socket::SocketAcceptException &e) {
			std::cerr << e.what() << std::endl;
		}
		catch (Socket::SocketReceiveException &e) {
			delete client;
			std::cerr << e.what() << std::endl; // TODO respond with the appropriate error
		}
		catch (Socket::SocketSendException &e) {
			delete client;
			delete response;
			delete request;
			std::cerr << e.what() << std::endl; // TODO respond with the appropriate error
		}
 	}
}

void Server::stop(void)
{
	return ;
}

bool Server::parseConfigFile(std::string configFile)
{
	(void)configFile;
	return true;
}