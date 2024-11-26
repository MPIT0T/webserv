/* ***************** */
/*      WebServ      */
/* ***************** */

#include "Server.hpp"

bool Server::_signals = false;

Server::Server( void )
{
	// Signal signal;
	signal(SIGINT, &handleSIGINT);
	signal(SIGQUIT, &handleSIGINT);
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
	const int MAX_EVENTS = 100;
	int epoll_fd = epoll_create1(0);
	if (epoll_fd == -1)
		throw std::runtime_error("Failed to create epoll instance");

	struct epoll_event	ev = {};
	struct epoll_event	events[MAX_EVENTS];

	ev.events = EPOLLIN;
	for (std::vector<Listen>::iterator it = _listens.begin(); it != _listens.end(); ++it)
	{
		std::stringstream ss;
		ss << "Listening on port http://" << it->getHost() << ":" << it->getPort();
		log.log(log.SERVER, ss.str().c_str());
		ev.data.fd = it->getSocket().getFd();
		if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, it->getSocket().getFd(), &ev) == -1)
			throw std::runtime_error("Failed to add listening socket to epoll instance");
	}

	log.log( log.SERVER, "The Server is UP !!");

	while (_signals == false)
	{
		int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if ((nfds  == -1) && _signals == false) {
			log.log( log.ERROR, "Failed to wait for events");
            break;
        }
		else if (_signals == true)
		{
			log.log( log.SERVER, "Server is shutting down...");
			break;
		}

		for (int i = 0; i < nfds; ++i)
		{
			int event_fd = events[i].data.fd;
			bool isListeningsocket = false;
			int listenID = 0;

            for (std::vector<Listen>::iterator it = _listens.begin(); it != _listens.end(); ++it)
			{
				if (event_fd == it->getSocket().getFd())
				{
					isListeningsocket = true;
					try
					{
						ClientInfo *client = it->getSocket().accept(listenID);
						log.log( log.CONNECTION, "Client ", client->fd(), " connected."); // TODO check les probs d'affichage
						ev.events = EPOLLIN;
						ev.data.fd = client->fd();
						if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client->fd(), &ev) == -1)
						{
							log.log( log.ERROR, "Failed to add client to epoll instance");
							delete client;
							continue;
						}
						client->setRouteAccess("/", it->getRoutes());
						clients.insert(std::make_pair(client->fd(), client));
					}
					catch (Socket::SocketAcceptException &e) {
						log.log(log.ERROR, "Failed to accept client");
						log.log(log.ERROR, e.what());
					}
				}
				listenID++;
			}
			if (!isListeningsocket && (events[i].events & EPOLLIN))
			{
				ClientInfo *client = clients.at(event_fd);

				try {
					Request *request = _listens.at(client->listenID()).getSocket().receive(client);
					log.log(log.TRACE, ("Metode : " + request->getType() + " --> " + request->getUri()).c_str());

					client->setRouteAccess(request->getUri(), _listens.at(listenID - 1).getRoutes());
					log.log(log.TRACE, ("Route Access : " + client->getRouteAccess()).c_str());

					SendResponse *response = new SendResponse(*request, _listens.at(client->listenID()), *client);
					response->makeMessageHeader();

					delete response;
					delete request;
				}
				catch (Socket::SocketReceiveException &e)
				{
					log.log( log.ERROR, "Failed to receive data from client");
					log.log( log.ERROR, e.what());
					close(event_fd);
					epoll_ctl(epoll_fd, EPOLL_CTL_DEL, event_fd, NULL);
					delete client;
					clients.erase(event_fd);
				}
			}
		}
	}
	close(epoll_fd);
    for (std::map<int, ClientInfo*>::iterator it = clients.begin(); it != clients.end(); ++it) {
        delete it->second;
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
		log.log( log.ERROR, e.what());
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

void Server::setEnv(char **env)
{
	_env = env;
}

char **Server::getEnv(void)
{
	return _env;
}

void	Server::handleSIGINT(int sig)
{
	(void)sig;
	std::cout << "\r";
	Server::_signals = true;
}
