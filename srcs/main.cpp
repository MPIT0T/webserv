/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:20:02 by mpitot            #+#    #+#             */
/*   Updated: 2024/10/22 15:02:31 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// CPP Includes
# include <iostream>
# include <iomanip>
# include <sstream>
# include <fstream>
# include <string>
# include <limits>
# include <cstdio>

// CPP Containers
# include <map>
# include <set>
# include <vector>
# include <algorithm>
# include <iterator>
# include <list>
# include <utility>

// C Includes
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <time.h>
# include <limits.h>
# include <errno.h>
# include <dirent.h>

// C System
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/time.h>

// C Network
# include <sys/socket.h>
# include <sys/select.h>
# include <arpa/inet.h>
# include <netinet/in.h>

#include <err.h>

char response[] = "HTTP/1.1 200 OK\r\n"
"Content-Type: text/html; charset=UTF-8\r\n\r\n"
"<!DOCTYPE html><html><head><title>Bye-bye baby bye-bye</title>"
"<style>body { background-color: #111 }"
"h1 { font-size:4cm; text-align: center; color: black;"
" text-shadow: 0 0 2mm red}</style></head>"
"<body><h1>Goodbye, world!</h1></body></html>\r\n";

/*int main()
{
	int one = 1, client_fd;
	struct sockaddr_in svr_addr, cli_addr;
	socklen_t sin_len = sizeof(cli_addr);

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		err(1, "can't open socket");

	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));

	int port = 8080;
	svr_addr.sin_family = AF_INET;
	svr_addr.sin_addr.s_addr = INADDR_ANY;
	svr_addr.sin_port = htons(port);
	printf("http://%s:%i\n", inet_ntoa(svr_addr.sin_addr), port);

	if (bind(sock, (struct sockaddr *) &svr_addr, sizeof(svr_addr)) == -1) {
		close(sock);
		err(1, "Can't bind");
	}
	listen(sock, 5);
	while (1) {
		client_fd = accept(sock, (struct sockaddr *) &cli_addr, &sin_len);
		printf("clien addr : %s \n", inet_ntoa(cli_addr.sin_addr));
		char buffer[2048];
		int len = recv(client_fd, buffer, 2048, 0);
		buffer[len] = 0;
		printf("%s\n", buffer);
		printf("got connection\n");

		if (client_fd == -1) {
			perror("Can't accept");
			continue;
		}

		write(client_fd, response, sizeof(response) - 1);
		close(client_fd);
	}
}*/

#include "Socket.hpp"
#include "Request.hpp"
#include "ClientInfo.hpp"

int		main(void)
{
	Socket		serverSock;
	ClientInfo	*clientSock;

	if (!serverSock.create())
	{
		std::cerr << "Creation error" << std::endl;
		return (1);
	}
	if (!serverSock.bind("127.0.0.1", 8080))
	{
		std::cerr << "bind error" << std::endl;
		return (1);
	}
	if (!serverSock.listen())
	{
		std::cerr << "Listen error" << std::endl;
		return (1);
	}

	std::cout << "Server listening" << std::endl;

	while (1)
	{
		clientSock = serverSock.accept();
		if (!clientSock)
		{
			std::cerr << "Accept error" << std::endl;
			return (1);
		}


		delete clientSock;
	}

	std::cout << "Client connected !" << std::endl;

	close(clientSock);
	return (0);
}
