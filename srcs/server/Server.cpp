/* ***************** */
/*      WebServ      */
/* ***************** */

#include "Server.hpp"
#include "Request.hpp"
#include "SendResponse.hpp"
#include <err.h>
#include <map>
#include "utils.hpp"

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
			std::cout << *request << std::endl;
			response = new SendResponse(request->getVersion(), "keep-alive","WebServ", "text/html", "www/main" + request->getUri(), OK); // TODO replace the file to send with the root file
			response->getNewMessage();
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
	std::string content;
	std::vector<std::string> tokens;
	std::vector<std::string> listenTokens;
	std::vector<Listen> listen;


	try {
		content = readFileContent(configFile);
		checkContentErrors(content);
		tokens = tokenizeConfig(content);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return false;
	}

	printTokens(tokens);
	printf("\n\n\n");
	listen = Server::setListen(tokens);

	_listen = listen;
	
	printListenVector(_listen);

	return true;
}

std::vector<Listen> Server::setListen(std::vector<std::string> tokens) {
    std::vector<Listen> listenConfigs;
    Listen currentListen;
    bool inListenBlock = false;
    bool inRoutesBlock = false;

    // Parcourir les tokens ligne par ligne
    for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); ++it) {
        std::string line = *it;

        // Vérifie les blocs de configuration
        if (line.find("listen:") != std::string::npos) {
            if (inListenBlock) {
                // Fin du bloc actuel, ajouter à la liste et réinitialiser
                listenConfigs.push_back(currentListen);
                currentListen = Listen();
            }
            inListenBlock = true;
        }
        
        // Port
        else if (line.find("port:") != std::string::npos) {
            int port = atoi(line.substr(line.find(":") + 1).c_str());
            currentListen.setPort(port);
        }

        // Host
        else if (line.find("host:") != std::string::npos) {
            std::string host = line.substr(line.find(":") + 1);
            currentListen.setHost(host);
        }

        // Server Name
        else if (line.find("server_name:") != std::string::npos) {
            std::string serverName = line.substr(line.find(":") + 1);
            currentListen.setServerName(serverName);
        }

        // Max Body Size
        else if (line.find("client_max_body_size:") != std::string::npos) {
            int maxBodySize = atoi(line.substr(line.find(":") + 1).c_str());
            currentListen.setMaxBodySize(maxBodySize);
        }

        // Error Pages
        else if (line.find("error_pages:") != std::string::npos) {
            std::map<int, std::string> errorPages;
            while (++it != tokens.end() && it->find("  ") != std::string::npos) {
                std::string errorLine = *it;
                int errorCode = atoi(errorLine.substr(0, errorLine.find(":")).c_str());
                std::string errorPage = errorLine.substr(errorLine.find(":") + 1);
                errorPages[errorCode] = errorPage;
            }
            currentListen.setErrorPages(errorPages);
            --it; // Revenir en arrière
        }

        // Début de Routes
        else if (line.find("routes:") != std::string::npos) {
            inRoutesBlock = true;
        }

        // Configuration des routes
        else if (inRoutesBlock && line.find("path:") != std::string::npos) {
            Route route;
            std::string path = line.substr(line.find(":") + 1);
            route.setPath(path);
            
            // Remplir les détails de la route
            while (++it != tokens.end() && it->find("  ") != std::string::npos) {
                std::string routeLine = *it;

                if (routeLine.find("allow_methods:") != std::string::npos) {
                    std::map<std::string, bool> methods;
                    while (++it != tokens.end() && it->find("    -") != std::string::npos) {
                        methods[it->substr(it->find("-") + 2)] = true;
                    }
                    route.setAllowMethods(methods);
                    --it;
                }
                else if (routeLine.find("root:") != std::string::npos) {
                    route.setRoot(routeLine.substr(routeLine.find(":") + 1));
                }
                else if (routeLine.find("directory_listing:") != std::string::npos) {
                    bool listing = (routeLine.find("true") != std::string::npos);
                    route.setDirectoryListing(listing);
                }
                else if (routeLine.find("default_file:") != std::string::npos) {
                    route.setHttpRedirect(routeLine.substr(routeLine.find(":") + 1));
                }
            }
            currentListen.setRoutes(std::vector<Route>(1, route));
            --it; // Revenir en arrière
        }
    }

    // Ajouter le dernier bloc Listen
    if (inListenBlock) {
        listenConfigs.push_back(currentListen);
    }

    return listenConfigs;
}
