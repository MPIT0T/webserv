//
// Created by gberthol on 10/22/24.
//

#pragma once

#include "Request.hpp"
#include <iostream>
#include "ClientInfo.hpp"
#include "Listen.hpp"
#include "PostMethod.hpp"
#include "ErrorExchange.hpp"

std::string getStatusDescription(eHttpStatusCode code);

class SendResponse
{
	public:
		SendResponse();
		SendResponse(const Request &request, const Listen &_listen, const ClientInfo &clientInfo);
		SendResponse(const SendResponse &old);
		~SendResponse();
		SendResponse &operator=(const SendResponse &old);


		void					makeMessageHeader();
		void					sendMessage();
		const std::string	 	&getMessage() const;
		void					generateMIME(const std::string &_contentType, const std::string &_fileToSend);

		void					errorMessage(eHttpStatusCode errorCode);

private:
		std::string			message;
		std::string			version;
		std::string			connection;
		std::string			serverName;
		std::string			contentType;
		std::string			fileToSend;
		eHttpStatusCode		code;
		std::string			bodyMessage;
		int 				fdClient;
		Listen				listen;
};

std::string mimeTypeOfFile(const std::string &fileToSend);