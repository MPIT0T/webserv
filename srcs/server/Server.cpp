/* ***************** */
/*      WebServ      */
/* ***************** */

#include "Server.hpp"
#include "Request.hpp"
#include "SendResponse.hpp"
#include <err.h>
#include <map>
#include <stack>

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
			// std::cout << *request << std::endl;
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
		content = trimConfig(readFileContent(configFile));
		checkJsonFormat(content);
		setListen(content);
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


	begin = content.find("{\"listen\":");
	if (begin == std::string::npos)
		throw std::exception();		//TODO throw good exception (no listen found)

	std::cout << content.substr(begin, content.size());

	begin += 10;
	std::cout << content.at(begin) << std::endl << std::endl;
	bracketStack.push(content.at(begin));
	begin++;

	// std::cout << content << std::endl << std::endl;
	for (end = begin; !bracketStack.empty(); end++)
	{
		c = content.at(end);
		// std::cout << c;
		if (c == '{' || c == '[' || c == '(')
		{
			bracketStack.push(c);
			std::cout << bracketStack.top();
		}
		else if (c == bracketMap.at(bracketStack.top()))
		{
			std::cout << c;
			bracketStack.pop();
		}
	}
	std::cout << std::endl << std::endl;
	std::string jsonContent = "{\"listen\":{\"port\":4242,\"host\":\"127.0.0.1\"},"
                          "\"server_name\":\"webserv.com\",\"default\":true,"
                          "\"root\":\"./www/main\",\"error_pages\":{\"404\":\"/404.html\","
                          "\"500\":\"/500.html\"},\"client_max_body_size\":\"2M\","
                          "\"routes\":[{\"path\":\"/\",\"allow_methods\":[\"GET\",\"POST\"],"
                          "\"root\":\"./www/main\",\"directory_listing\":false,"
                          "\"default_file\":\"index.html\"},{\"path\":\"/redirect\","
                          "\"http_redirect\":\"https://anotherwebsite.com\"},"
                          "{\"path\":\"/kapouet\",\"root\":\"/tmp/www\",\"directory_listing\":true},"
                          "{\"path\":\"/cgi-bin\",\"allow_methods\":[\"GET\",\"POST\"],"
                          "\"cgi\":{\"extension\":\".php\",\"path\":\"/usr/bin/php-cgi\","
                          "\"upload_dir\":\"/var/uploads\"},\"default_file\":\"index.php\"},"
                          "{\"path\":\"/files\",\"allow_methods\":[\"POST\"],"
                          "\"upload_dir\":\"/var/uploads\"}]}";
	// listens.push_back(Listen(content.substr(begin, end - begin)));
	std::cout << jsonContent << std::endl << std::endl;
	listens.push_back(Listen(jsonContent));
	// std::cout << content << std::endl << std::endl;
	// content = content.substr(end, content.size() - end);
	// std::cout << content << std::endl << std::endl << std::endl;
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
