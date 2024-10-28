/* ***************** */
/*      WebServ      */
/* ***************** */

#include "Server.hpp"
#include "Request.hpp"
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
    _socket.create();
    _socket.bind("127.0.0.1", 4242);
    _socket.listen();
}

void Server::run(void)
{
    ClientInfo  *client;
    Request     *request;
    std::string response;

    std::cout << "Waiting for connection..." << std::endl << std::endl;

    while (true)
    {
        client = _socket.accept();
        request = _socket.receive(client);
        std::cout << "Client connected." << std::endl << std::endl;
        if (_socket.getFd() < 0)
        {
            std::cerr << "Can't accept client." << std::endl << std::endl;
            delete client;
            delete request;
            continue ;
        }

        { /// to remove
            std::ifstream file("www/main/index.html");
            if (!file.is_open())
                err(1, "Can't open index.html");
            response = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n";
            response = response + std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            file.close();
        } ///

        _socket.send(client, response);
        delete request;
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