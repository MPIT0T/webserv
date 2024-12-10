//
// Created by gberthol on 12/2/24.
//

#pragma once

#include <iostream>
#include "utilsExchange.hpp"

class Listen;


class ErrorExchange
{
	public:
		ErrorExchange();
		ErrorExchange(const Listen &listen);
		ErrorExchange(const ErrorExchange &old);
		~ErrorExchange();
		ErrorExchange &operator=(const ErrorExchange &old);

		void	testResponses(const std::string &newFileToSend, eHttpStatusCode code);
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
