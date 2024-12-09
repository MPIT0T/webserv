//
// Created by gberthol on 12/2/24.
//

#pragma once

#include <iostream>
#include "ErrorExchange.hpp"
#include "ClientInfo.hpp"
#include "Request.hpp"
#include <unistd.h>

class ExchangeHandling
{
	public:
		ExchangeHandling();
		ExchangeHandling(std::string request);
		ExchangeHandling(const ExchangeHandling &old);
		~ExchangeHandling();
		ExchangeHandling &operator=(const ExchangeHandling &old);

		void		sendResponse();
		void		generateMessage();
		void		generateHeader();

	private:
		ClientInfo		*_client;
		Listen			_listen;
		Request			_request;
		ErrorExchange	_error;
		std::string		_message;
		std::string		_fileToSend;
		std::string 	_header;
};
