/* ***************** */
/*      WebServ      */
/* ***************** */

#include "Server.hpp"
#include "SendResponse.hpp"
#include <err.h>

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
    if (_socket.create() == false)
        throw std::exception();
    if (_socket.bind("0.0.0.0", 4242) == false)
        throw std::exception();
    if (_socket.listen() == false)
        throw std::exception();
    return ;
}

void Server::run(void)
{
    ClientInfo		*client;
	SendResponse	*response;

    std::cout << "Waiting for connection..." << std::endl << std::endl;

    while (true)
    {
        client = _socket.accept();
        _socket.receive(client);
		response = new SendResponse("HTTP/1.1", "keep-alive","webServ", "text/html",
		"index.html", OK);
        std::cout << "Client connected." << std::endl << std::endl;
        if (_socket.getFd() < 0)
        {
            std::cerr << "Can't accept client." << std::endl << std::endl;
            delete client;
            continue ;
        }
		response->getNewMessage();
        _socket.send(client, response->getMessage());
        delete client;
    }
}

void Server::stop( void )
{
    return ;
}

bool Server::parseConfigFile( std::string configFile )
{
    (void)configFile;
    return true;
}