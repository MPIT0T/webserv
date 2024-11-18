/* ***************** */
/*      WebServ      */
/* ***************** */

#include "Server.hpp"
#include "Request.hpp"
#include "SendResponse.hpp"
#include <err.h>
#include <poll.h>
#include <map>
#include <stack>
#include <algorithm>
#include "utils.hpp"

Server::Server( void )
{
	_signals = Signal();
	_socket = Socket();
}

Server::Server( const Server &src )
{
	*this = src;
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
	_socket.bind("127.0.0.1", 8080);
	_socket.listen();
}

template <typename T, typename Predicate>		//TODO deplacer
typename std::vector<T>::iterator remove_if_custom(std::vector<T>& vec, Predicate pred) {
	typename std::vector<T>::iterator it = vec.begin();
	while (it != vec.end()) {
		if (pred(*it)) {
			it = vec.erase(it);  // Erase and get the next iterator
		} else {
			++it;
		}
	}
	return it;  // Return the iterator pointing to the new end
}


struct FDChecker {
	bool operator()(const pollfd& p) const {
		return p.fd == -1;
	}
};

void Server::run(void)
{
	std::vector<pollfd>				fds;
	std::map<int, ClientInfo*>		clients;
	pollfd							listen_fd;

	listen_fd.fd = _socket.getFd();
	listen_fd.events = POLLIN;
	listen_fd.revents = 0;
	fds.push_back(listen_fd);

	std::cout << "Waiting for connection..." << std::endl << std::endl;

	while (42)
	{
		int ret = poll(&fds[0], fds.size(), -1);
		if (ret < 0)
		{
			std::cerr << "Poll error" << std::endl;
			break ;
		}
		for (size_t i = 0; i < fds.size(); ++i)
		{
			if (fds[i].fd == listen_fd.fd && (fds[i].revents & POLLIN))
			{
				try
				{
					ClientInfo *client = _socket.accept();
					std::cout << "Client connected." << std::endl;

					pollfd client_fd;
					client_fd.fd = client->fd();
					client_fd.events = POLLIN;
					client_fd.revents = 0;
					fds.push_back(client_fd);
					clients.insert(std::make_pair(client_fd.fd, client));
				}
				catch (Socket::SocketAcceptException &e)
				{
					std::cerr << e.what() << std::endl;
				}
			}
			else if (fds[i].revents & POLLIN)
			{
				int client_fd = fds[i].fd;
				ClientInfo *client = clients[client_fd];

				try
				{
					Request *request = _socket.receive(client);
					std::cout << "Request received from client " << client_fd << std::endl;

					SendResponse *response = new SendResponse(request->getVersion(),
															  request->getHeaders().at("Connection"),
															  "WebServ",
															  request->getHeaders().at("Accept"),
															  "www/main" + request->getUri(),
															  OK,
															  client->fd());
					response->getNewMessage();

					delete response;
				}
				catch (Socket::SocketReceiveException &e)
				{
					std::cerr << e.what() << std::endl;
					close(client_fd);
					fds[i].fd = -1;
					delete client;
					clients.erase(client_fd);
				}
			}
		}
		fds.erase(remove_if_custom(fds, FDChecker()), fds.end());
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
		content = trimConfig(readFileContent(configFile));
		checkJsonFormat(content);
		_listen = setListen(content);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return false;
	}
	return true;
}

void Server::checkJsonFormat(const std::string& content)
{
	std::stack<char>	brackets;
	char				c;
	char				openBracket;

	for (std::string::size_type i = 0; i < content.size(); ++i)
	{
		c = content[i];

		if (c == '{' || c == '[' || c == '(')
			brackets.push(c);
		else if (c == '}' || c == ']' || c == ')')
		{
			if (brackets.empty())
				throw ServerConfigJSONFormatException();

			openBracket = brackets.top();
			brackets.pop();

			if ((c == '}' && openBracket != '{') ||
				(c == ']' && openBracket != '[') ||
				(c == ')' && openBracket != '('))
				throw ServerConfigJSONFormatException();
		}
	}
	if (!brackets.empty())
		throw ServerConfigJSONFormatException();
}

std::vector<Listen> Server::setListen(std::string content)
{
	std::vector<Listen>			listens;
	std::stack<char>			bracketStack;
	std::map<char, char>		bracketMap;
	std::string::size_type		begin;
	std::string::size_type		end;
	char						c;

	bracketMap.insert(std::make_pair('{', '}'));
	bracketMap.insert(std::make_pair('[', ']'));
	bracketMap.insert(std::make_pair('(', ')'));


	while (42)
	{
		begin = content.find("{\"listen\":");
		if (begin == std::string::npos)
			break ;
		bracketStack.push(content.at(begin));
		for (end = begin + 1; !bracketStack.empty(); end++)
		{
			c = content.at(end);
			if (c == '{' || c == '[' || c == '(')
				bracketStack.push(c);
			else if (c == bracketMap.at(bracketStack.top()))
				bracketStack.pop();
		}
		listens.push_back(Listen(content.substr(begin, end - begin)));
		content = content.substr(end, content.size() - end);
	}
	return listens;
}

std::string Server::trimConfig(const std::string& config) {
    std::string trimmed;
    bool inQuotes = false;

    for (std::string::size_type i = 0; i < config.size(); ++i) {
        char c = config[i];

        if (c == '"') {
            inQuotes = !inQuotes;
            trimmed += c;
        }
        else if (inQuotes || (c != ' ' && c != '\t' && c != '\n')) {
            trimmed += c;
        }
    }
    return trimmed;
}


/* Exceptions *************************************************************** */
const char* Server::ServerConfigJSONFormatException::what() const throw()
{
	return "JSON bracket format non valid";
}
