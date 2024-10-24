/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:36:46 by mbrousse          #+#    #+#             */
/*   Updated: 2024/10/24 11:07:50 by mbrousse         ###   ########.fr       */
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
    if (_socket.bind("webserv.com", 8080) == false)
        throw std::exception();
    if (_socket.listen() == false)
        throw std::exception();
    return ;
}
    char response[] = "HTTP/1.1 200 OK\r\n"
"Content-Type: text/html; charset=UTF-8\r\n\r\n"
"<!DOCTYPE html><html><head><title>Bye-bye baby bye-bye</title>"
"<style>body { background-color: #111 }"
"h1 { font-size:4cm; text-align: center; color: black;"
" text-shadow: 0 0 2mm red}</style></head>"
"<body><h1>Goodbye, world!</h1></body></html>\r\n";

void Server::run( void )
{
    
    bool running = true;
    while(running){
        int client_fd = _socket.accept();
        printf("got connection\n");
        // char buffer[2048];
        // int len = _socket.receive(, buffer, 2048);
        // buffer[len] = 0;
        // printf("%s\n", buffer);
        if (_socket.getFd() == -1) {
			perror("Can't accept");
			continue;
		}
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