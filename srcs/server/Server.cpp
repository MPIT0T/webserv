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
	
}

void Server::init(void)
{
	_socket.create();
	_socket.bind("127.0.0.1", 8080);
	_socket.listen();
}

struct FDChecker {
	bool operator()(const pollfd& p) const {
		return p.fd == -1;
	}
};

void Server::run(void)
{
	Logger log( this->getEnv() );
	const int MAX_EVENTS = 1000; // Maximum number of events to handle at once
    int epoll_fd = epoll_create1(0); // Create an epoll instance
    if (epoll_fd == -1) {
		throw std::runtime_error("Failed to create epoll instance");
    }

     // Track clients by their file descriptor
    struct epoll_event ev, events[MAX_EVENTS];

    // Add the listening socket to the epoll instance
    ev.events = EPOLLIN;
    ev.data.fd = _socket.getFd();
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, _socket.getFd(), &ev) == -1) {
		throw std::runtime_error("Failed to add listening socket to epoll instance");
    }

    log.log( log.SERVER, "The Server is UP !!");

    while (_signals == false) {
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

        for (int i = 0; i < nfds; ++i) {
            int event_fd = events[i].data.fd;

            if (event_fd == _socket.getFd()) {
                // Handle new client connections
                try {
                    ClientInfo *client = _socket.accept();
					log.log( log.CONNECTION, "Client connected.");

                    ev.events = EPOLLIN;
                    ev.data.fd = client->fd();
                    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client->fd(), &ev) == -1) {
                        log.log( log.ERROR, "Failed to add client to epoll instance");
                        delete client; // Cleanup on failure
                        continue;
                    }
                    clients.insert(std::make_pair(client->fd(), client));
                } catch (Socket::SocketAcceptException &e) {
                    std::cerr << e.what() << std::endl;
                }
            } else if (events[i].events & EPOLLIN) {
                // Handle data from an existing client
                ClientInfo *client = clients[event_fd];
                try {
                    Request *request = _socket.receive(client);
					log.log( log.TRACE, ("Metode : " + request->getType() + " --> " + request->getUri()).c_str());

                    SendResponse *response = new SendResponse(
                        request->getVersion(),
                        request->getHeaders().at("Connection"),
                        "WebServ",
                        request->getHeaders().at("Accept"),
                        "www/main" + request->getUri(),
                        OK,
                        client->fd()
                    );
                    response->getNewMessage();
                    delete response;
					delete request;
                } catch (Socket::SocketReceiveException &e) {
                    std::cerr << e.what() << std::endl;
                    close(event_fd);
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, event_fd, NULL); // Remove from epoll
                    delete client;
                    clients.erase(event_fd);
                }
            }
        }
    }

    // Cleanup
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
