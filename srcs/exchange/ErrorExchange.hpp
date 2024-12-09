//
// Created by gberthol on 12/2/24.
//

#pragma once

#include <iostream>

class Listen;

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

class ErrorExchange
{
	public:
		ErrorExchange();
		ErrorExchange(const Listen &listen);
		ErrorExchange(const ErrorExchange &old);
		~ErrorExchange();
		ErrorExchange &operator=(const ErrorExchange &old);

		void	testResponses(const std::string &newFileToSend);
		void	generateErrorPage();


		eHttpStatusCode getCode() const;
		const Listen &getListen() const;
		const std::string &getMessage() const;
		const std::string &getFileToSend() const;

		void setCode(eHttpStatusCode code);
		void setListen(const Listen &listen);
		void setMessage(const std::string &message);
		void setFileToSend(const std::string &fileToSend);

private:
	eHttpStatusCode		_code;
	Listen				*_listen;
	std::string			_message;
	std::string			_fileToSend;
};
