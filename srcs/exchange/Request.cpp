//
// Created by gberthol on 12/2/24.
//

#include "Request.hpp"
#include <unistd.h>
#include "Listen.hpp"
#include "ClientInfo.hpp"

Request::Request()
{

}

Request::Request(const std::string &request, ClientInfo *client, const Listen &listen)
{
	_request = request;
	_client = client;
	_listen = new Listen(listen);
	_code = OK;
}

Request::Request(const Request &old)
{
	_request = old._request;
	_client = old._client;
	_listen = old._listen;
	_code = old._code;
}

Request::~Request()
{
	delete _listen;
}

Request  &Request::operator=(const Request &old)
{
	_request = old._request;
	_client = old._client;
	_listen = old._listen;
	_code = old._code;
	return *this;
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

	_code = NOT_IMPLEMENTED;
	switch (methodType[_type])
	{
		case 1:
			if (!_listen->getRoutes()[_uri].getDefaultFile().empty())
				_fileToSend = _client->getRouteAccess() + "/" + _listen->getRoutes()[_uri].getDefaultFile();
			else
				_fileToSend = _client->getRouteAccess() + "/" + _uri;
			_code = OK;
			break;
		case 2:
			std::cout << "Method POST" << std::endl;
			break;
		case 3:
			std::cout << "Method DELETE" << std::endl;
			break;
		default:
			if (_type.empty())
			{
				_code = NOT_FOUND;
				std::cout << "page not found" << std::endl;
			}
			std::cout << "Other method" << std::endl;
	}
}

void	Request::errorRequest()
{
	int	space = 0;
	int	lineBreak = 0;

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

eHttpStatusCode Request::getCode() const
{
	return _code;
}

const std::string &Request::getType() const
{
	return _type;
}

const std::string &Request::getBody() const
{
	return _body;
}

const std::string &Request::getRequest() const
{
	return _request;
}

ClientInfo *Request::getClient() const
{
	return _client;
}

Listen *Request::getListen() const
{
	return _listen;
}

const std::map<std::string, std::string> &Request::getHeaders() const
{
	return _headers;
}

std::ostream &operator<<(std::ostream &OUT, const Request& request)
{
	OUT << "Type: " << request.getType() << std::endl;
	OUT << "URI: " << request.getUri() << std::endl;

	OUT << "Version: " << request.getVersion() << std::endl;
	OUT << "body: " << request.getBody() << std::endl;
	return (OUT);
}
