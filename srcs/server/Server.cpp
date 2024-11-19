/* ***************** */
/*      WebServ      */
/* ***************** */

#include "Server.hpp"
#include "Request.hpp"
#include "SendResponse.hpp"
#include <err.h>
#include <sys/epoll.h>
#include <map>
#include <stack>
#include <algorithm>
#include "utils.hpp"

Server::Server( void )
{
	_signals = Signal();
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
	for (std::vector<Listen>::iterator it = _listens.begin(); it != _listens.end(); ++it)
	{
		it->setSocket(it->getHost(), it->getPort());
	}
}

void Server::run(void)
{
	const int MAX_EVENTS = 1000;
	int epoll_fd = epoll_create1(0);
	if (epoll_fd == -1)
		throw std::runtime_error("Failed to create epoll instance");

	std::map<int, ClientInfo *> clients;
	epoll_event ev;
	epoll_event events[MAX_EVENTS];

	for (std::vector<Listen>::iterator it = _listens.begin(); it != _listens.end(); ++it)
	{
		ev.events = EPOLLIN;
		ev.data.fd = it->getSocket().getFd();
		if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, ev.data.fd, &ev) == -1)
			throw std::runtime_error("Failed to add listening socket to epoll instance");
	}

	std::cout << "The Server is UP !!" << std::endl << std::endl;

	while (42)
	{
		int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
		if (nfds == -1)
			throw std::runtime_error("epoll_wait() error");

		for (int i = 0; i < nfds; ++i)
		{
			int event_fd = events[i].data.fd;
			bool isListeningSocket = false;

			for (std::vector<Listen>::iterator it = _listens.begin(); it != _listens.end(); ++it)
			{
				if (event_fd == it->getSocket().getFd())
				{
					isListeningSocket = true;
					try
					{
						ClientInfo *client = it->getSocket().accept();
						std::cout << "Client connected on socket " << event_fd << std::endl;

						epoll_event ev;
						ev.events = EPOLLIN;
						ev.data.fd = client->fd();
						if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client->fd(), &ev) == -1)
						{
							//TODO log error but continue
							delete client;
							continue ;
						}


					}
				}
			}
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
		content = trimConfig(readFileContent(configFile));
		checkJsonFormat(content);
		_listens = setListen(content);
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
