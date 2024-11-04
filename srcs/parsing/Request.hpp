//
// Created by gberthol on 10/21/24.
//

#pragma once

#include <iostream>
#include <vector>
#include "Header.hpp"

class Request
{
	public:

		Request();
		Request(const Request &old);
		~Request();
		Request &operator=(const Request &old);

		void						setRequest(const std::string &request);
		const std::string			&getType() const;
		const std::string			&getUri() const;
		const std::vector<Header>	&getHeaders() const;
		const std::string			&getVersion() const;
		const std::string			&getBody() const;

private:
		std::string					type;
		std::string					uri;
		std::vector<Header>			headers;
		std::string					version;
		std::string					body;
		std::string					contentType;	// text/html or img
		std::string					connection;		// keep alive ?
};

std::ostream	&operator<<(std::ostream &OUT, const Request &request);