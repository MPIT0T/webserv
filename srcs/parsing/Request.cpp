//
// Created by gberthol on 10/21/24.
//

#include "Request.hpp"
#include <vector>

Request::Request()
{
}

Request::~Request()
{
	headers.clear();
}

Request::Request(const Request &old)
{
	this->type = old.type;
	this->uri = old.uri;
	this->headers = old.headers;
	this->version = old.version;
	this->body = old.body;
}

Request &Request::operator=(const Request &old)
{
	this->type = old.type;
	this->uri = old.uri;
	this->headers = old.headers;
	this->version = old.version;
	this->body = old.body;
	return *this;
}

void Request::setRequest(const std::string &request)
{
	std::string requestCpy(request);
	std::string tmp;

	type = requestCpy.substr(0, requestCpy.find( ' '));
	requestCpy.erase(0, requestCpy.find( ' ') + 1);
	uri  = requestCpy.substr(0, requestCpy.find( ' '));
	if (uri == "/")
		uri = uri + "index.html";
	requestCpy.erase(0, requestCpy.find( ' ') + 1);
	version  = requestCpy.substr(0, requestCpy.find( '\n'));
	requestCpy.erase(0, requestCpy.find( '\n') + 1);
	while (!requestCpy.empty() && requestCpy.at(0) != '\n')
	{
		tmp = requestCpy.substr(0, requestCpy.find(": "));
		requestCpy.erase(0, requestCpy.find( ": ") + 2);
		headers[tmp] = requestCpy.substr(0, requestCpy.find( '\n'));
		if (requestCpy.find('\n') > requestCpy.size())
			requestCpy.clear();
		else
			requestCpy.erase(0, requestCpy.find( '\n') + 1);
	}
	requestCpy.erase(0, 1);
	body = requestCpy;
}

const std::string &Request::getType() const
{
	return type;
}

const std::string &Request::getUri() const
{
	return uri;
}

const std::map<std::string, std::string>	&Request::getHeaders() const
{
	return headers;
}

const std::string &Request::getVersion() const
{
	return version;
}

const std::string &Request::getBody() const
{
	return body;
}

std::ostream &operator<<(std::ostream &OUT, const Request& request)
{
	std::map<std::string, std::string>::const_iterator	end = request.getHeaders().end();

	OUT << "Type: " << request.getType() << std::endl;
	OUT << "URI: " << request.getUri() << std::endl;

	for (std::map<std::string, std::string>::const_iterator begin = request.getHeaders().begin(); begin != end; begin++)
		OUT << begin->first << " " << begin->second << std::endl;
	OUT << "Version: " << request.getVersion() << std::endl;
	OUT << "body: " << request.getBody() << std::endl;
	return (OUT);
}
