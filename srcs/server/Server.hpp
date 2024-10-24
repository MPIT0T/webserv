/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:35:11 by mbrousse          #+#    #+#             */
/*   Updated: 2024/10/24 11:32:44 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include "Socket.hpp"
# include <unistd.h>
# include <fstream>
class Server{
private:
    Socket _socket;
    
public:
    Server( void );
    Server( const Server &src );
    Server &operator=( const Server &src );
    
    ~Server();


    bool parseConfigFile( std::string configFile );
    void init( void );    
    void run( void );
    void stop( void );
};

#endif // Server_HPP