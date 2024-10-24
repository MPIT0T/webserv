/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:36:46 by mbrousse          #+#    #+#             */
/*   Updated: 2024/10/24 12:57:20 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

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

void Server::init( void )
{
    if (_socket.create() == false)
        throw std::exception();
    if (_socket.bind("webserv.com", 4242) == false)
        throw std::exception();
    if (_socket.listen() == false)
        throw std::exception();
    return ;
}

void Server::run( void )
{
    
    bool running = true;
    printf("waiting for connection\n\n");
    while(running){
        int client_fd = _socket.accept();
		_socket.receive(client_fd);
		printf("got connection\n\n");
        if (_socket.getFd() == -1) {
			perror("Can't accept\n");
			continue;
		}
        //to remouve
        std::ifstream file("www/main/index.html");
	    if (!file.is_open())
		    err(1, "Can't open index.html");
	    std::string http_header = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n";
	    std::string response = http_header + std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	    file.close();
        ///
        _socket.send(client_fd, response);
        close(client_fd);
    }
    return ;
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