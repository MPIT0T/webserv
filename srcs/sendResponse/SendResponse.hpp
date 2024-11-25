//
// Created by gberthol on 10/22/24.
//

#pragma once

#include "Request.hpp"
#include <iostream>
#include "ClientInfo.hpp"
#include "Listen.hpp"

enum eHttpStatusCode {
	// 1xx: Informational responses
	CONTINUE = 100,
	SWITCHING_PROTOCOLS = 101,
	PROCESSING = 102,

	// 2xx: Success
	OK = 200,
	CREATED = 201,
	ACCEPTED = 202,
	NON_AUTHORITATIVE_INFORMATION = 203,
	NO_CONTENT = 204,
	RESET_CONTENT = 205,
	PARTIAL_CONTENT = 206,

	// 3xx: Redirection
	MULTIPLE_CHOICES = 300,
	MOVED_PERMANENTLY = 301,
	FOUND = 302,
	SEE_OTHER = 303,
	NOT_MODIFIED = 304,
	TEMPORARY_REDIRECT = 307,
	PERMANENT_REDIRECT = 308,

	// 4xx: Client errors
	BAD_REQUEST = 400,
	UNAUTHORIZED = 401,
	PAYMENT_REQUIRED = 402,
	FORBIDDEN = 403,
	NOT_FOUND = 404,
	METHOD_NOT_ALLOWED = 405,
	NOT_ACCEPTABLE = 406,
	REQUEST_TIMEOUT = 408,
	CONFLICT = 409,
	GONE = 410,
	LENGTH_REQUIRED = 411,
	PAYLOAD_TOO_LARGE = 413,
	URI_TOO_LONG = 414,
	UNSUPPORTED_MEDIA_TYPE = 415,
	RANGE_NOT_SATISFIABLE = 416,
	EXPECTATION_FAILED = 417,
	TOO_MANY_REQUESTS = 429,

	// 5xx: Server errors
	INTERNAL_SERVER_ERROR = 500,
	NOT_IMPLEMENTED = 501,
	BAD_GATEWAY = 502,
	SERVICE_UNAVAILABLE = 503,
	GATEWAY_TIMEOUT = 504,
	HTTP_VERSION_NOT_SUPPORTED = 505,
	INSUFFICIENT_STORAGE = 507
};

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