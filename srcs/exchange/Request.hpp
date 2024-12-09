//
// Created by gberthol on 12/2/24.
//

#pragma once

#include <iostream>
#include "ClientInfo.hpp"
#include "ErrorExchange.hpp"
#include <map>

class Request
{
	public:
		Request();
		Request(const std::string &request, ClientInfo *client, const Listen &listen);
		Request(const Request &old);
		~Request();
		Request &operator=(const Request &old);

		void	parseRequest();
		void	makeRequestMethod();
		void	errorRequest();

		const std::string &getVersion() const;
		const std::string &getUri() const;
		const std::string &getConnection() const;
		const std::string &getMessage() const;
		const std::string &getFileToSend() const;

private:
		eHttpStatusCode _code;
		std::string		_type;
		std::string		_uri;
		std::string		_body;
		std::string		_message;
		std::string		_fileToSend;
		std::string		_request;
		ClientInfo		*_client;
		Listen			*_listen;
		std::string		_version;
		std::string		_connection;

		std::map<std::string, std::string>		_headers;
};
