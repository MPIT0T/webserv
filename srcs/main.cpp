/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:20:02 by mpitot            #+#    #+#             */
/*   Updated: 2024/10/24 12:58:56 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ManageArgs.hpp"
#include "Server.hpp"

Server *g_server;

int main(int argc, char *argv[])
{
	Server server;
	g_server = &server;
	ManageArgs args(argc, argv);

	if (!args.checkArgs())
		return (EXIT_FAILURE);
	try{
		if(server.parseConfigFile(args.getArgv()[1]) == false)
			return (EXIT_FAILURE);
		
		server.init();
		server.run();
	}
	catch(const std::exception& e){
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
