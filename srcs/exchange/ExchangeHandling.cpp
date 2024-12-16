//
// Created by gberthol on 12/2/24.
//

#include "ExchangeHandling.hpp"
#include <sys/stat.h>
#include <fcntl.h>
#include "Listen.hpp"

ExchangeHandling::ExchangeHandling(const std::string& request, ClientInfo *client, const Listen &listen)
{
	_message = request;
	_client = client;
	_listen = new Listen(listen);
	_request = Request(request, client, listen);
	_error = ErrorExchange(*_listen);
}

ExchangeHandling::~ExchangeHandling()
{
	delete _listen;
}

ExchangeHandling::ExchangeHandling(const ExchangeHandling &old)
{
	this->_message = old._message;
}

ExchangeHandling &ExchangeHandling::operator=(const ExchangeHandling &old)
{
	this->_message = old._message;
	return *this;
}

void ExchangeHandling::sendResponse()
{
	int				fd;
	char			tab[1024];
	size_t 			nbrRead = 1;

	write(_client->fd(), _header.c_str(), _header.size());
	if (_fileToSend.empty())
	{
		write(_client->fd(), _message.c_str(), _message.size());
		return ;
	}
	fd = open(_fileToSend.c_str(), O_RDONLY);
	if (fd <= 0)
		return ;
	while (nbrRead > 0)
	{
		nbrRead = read(fd, tab, 1023);
		tab[nbrRead] = 0;
		write(_client->fd(), tab, nbrRead);
	}
	close(fd);
}

void ExchangeHandling::generateMessage()
{
	_request.errorRequest();
	_request.parseRequest();
	_client->setRouteAccess(_request.getUri(), _listen->getRoutes());
	_request.makeRequestMethod();
	_message = _request.getMessage();
	_fileToSend = _request.getFileToSend();
	_error.testResponses(_fileToSend, _request.getCode());
	_error.generateErrorPage();
	if (_error.getCode() >= 400)
	{
		_message = _error.getMessage();
		_fileToSend = _error.getFileToSend();
	}
	generateHeader();
	sendResponse();
}

void ExchangeHandling::generateHeader()
{
	struct stat		buf;

	//clear old message
	_header.clear();

	//get http version
	_header = "HTTP/1.1";

	//get http response status
	_header += ' ';
	_header.append(ft_itoa((unsigned  int)_error.getCode()));
	_header += ' ';
	_header.append(getStatusDescription(_error.getCode()));

	//get time format
	_header.append("\nDate: ");
	_header.append(getTimeFormat());

	//get server
	_header.append("Server: ");
	_header.append(_listen->getServerName());
	_header.push_back('\n');

	//get content type
	_header.append("Content-Type: ");
	if (!_fileToSend.empty())
	{
		if (_request.getHeaders().find("Accept") != _request.getHeaders().end())
			_header.append(generateMIME(_fileToSend, _request.getHeaders().at("Accept")));
		else
			_header.append(generateMIME(_fileToSend, "text/html"));
	}
	else
		_header.append(generateMIME(_message, _request.getHeaders().at("Accept")));

	//get message length
	_header.append("\nContent-Length: ");
	if (!_fileToSend.empty())
	{
		stat(_fileToSend.c_str(), &buf);
		_header.append(ft_itoa(buf.st_size));
	}
	else
		_header.append(ft_itoa(_message.size()));

	//get connection
	_header.append("\nConnection: ");
	_header.append("keep-alive");
	_header.append("\n\n");
}

ExchangeHandling::ExchangeHandling()
{
	 _client = NULL;
	 _listen = NULL;
}
