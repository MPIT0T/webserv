//
// Created by gberthol on 12/2/24.
//

#include "Request.hpp"
#include <unistd.h>
#include "Listen.hpp"

Request::Request()
{

}

Request::Request(const std::string &request, ClientInfo *client, const Listen &listen)
{
	_request = request;
	_client = client;
	*_listen = listen;
	_code = OK;
}

Request::Request(const Request &old)
{

}

Request::~Request()
{

}

Request  &Request::operator=(const Request &old)
{
}

void	Request::parseRequest()
{
	std::string tmp;

	_type = _request.substr(0, _request.find( ' '));
	_request.erase(0, _request.find( ' ') + 1);
	_uri  = _request.substr(0, _request.find( ' '));
	_request.erase(0, _request.find( ' ') + 1);
	if (_uri.size() > 2000)
		_code = URI_TOO_LONG;
	_version  = _request.substr(0, _request.find( '\n'));
	_request.erase(0, _request.find( '\n') + 1);
	while (!_request.empty() && _request.at(0) != '\n')
	{
		tmp = _request.substr(0, _request.find(": "));
		_request.erase(0, _request.find( ": ") + 2);
		_headers[tmp] = _request.substr(0, _request.find( '\n'));
		if (_request.find('\n') == std::string::npos)
			_request.clear();
		else
			_request.erase(0, _request.find( '\n') + 1);
	}
	_request.erase(0, 1);
	_body = _request;
}

void	Request::makeRequestMethod()
{
	std::map<std::string, int> methodType;

	methodType["GET"] = 1;
	methodType["POST"] = 2;
	methodType["DELETE"] = 3;

	switch (methodType[_type])
	{
		case 1:
			_fileToSend = _client->getRouteAccess() + _uri;
			break;
		case 2:
			std::cout << "Method POST" << std::endl;
			break;
		case 3:
			std::cout << "Method DELETE" << std::endl;
			break;
		default:
			std::cout << "Other method" << std::endl;
	}
}

void	Request::errorRequest()
{
	int	space;
	int	lineBreak;

	if (_request.empty())
		_code = BAD_REQUEST;
	for (size_t i = 0; i < _request.size(); i++)
	{
		space += (_request.at(i) == ' ');
		lineBreak += (_request.at(i) == '\n');
	}
	if (space < 3 || lineBreak < 2)
		_code = BAD_REQUEST;
}

const std::string &Request::getVersion() const
{
	return _version;
}

const std::string &Request::getUri() const
{
	return _uri;
}

const std::string &Request::getConnection() const
{
	return _connection;
}

const std::string &Request::getMessage() const
{
	return _message;
}

const std::string &Request::getFileToSend() const
{
	return _fileToSend;
}
