//
// Created by gberthol on 12/2/24.
//

#include "ErrorExchange.hpp"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "Listen.hpp"
#include "utils.hpp"
#include <string.h>

ErrorExchange::ErrorExchange()
{

}

ErrorExchange::~ErrorExchange()
{

}

ErrorExchange::ErrorExchange(const ErrorExchange &old)
{
	this->_fileToSend = old._fileToSend;
	this->_code = old._code;
	this->_listen = old._listen;
	this->_message = old._message;
}

ErrorExchange::ErrorExchange(const Listen &listen)
{
	_listen = new Listen(listen);
}

ErrorExchange &ErrorExchange::operator=(const ErrorExchange &old)
{
	this->_fileToSend = old._fileToSend;
	this->_code = old._code;
	this->_listen = old._listen;
	this->_message = old._message;
	return *this;
}

void ErrorExchange::testResponses(const std::string &newFileToSend, eHttpStatusCode code)
{
	_code = code;
	_fileToSend = newFileToSend;
	if (!_fileToSend.empty())
	{
		if (access(_fileToSend.c_str(), F_OK) == -1)
			_code = NOT_FOUND;
		if (access(_fileToSend.c_str(), R_OK) == -1)
		{
			std::cout << strerror(errno) << std::endl;
			_code = FORBIDDEN;
		}
	}
}

void ErrorExchange::generateErrorPage()
{
	if (_code >= 400)
		_fileToSend = _listen->getErrorPages()[_code];
	if (!_fileToSend.empty())
	{
		if (access(_fileToSend.c_str(), R_OK) == -1)
			_message = errorPage(_code);
	}
}

eHttpStatusCode ErrorExchange::getCode() const
{
	return _code;
}

const Listen &ErrorExchange::getListen() const
{
	return *_listen;
}

const std::string &ErrorExchange::getMessage() const
{
	return _message;
}

const std::string &ErrorExchange::getFileToSend() const
{
	return _fileToSend;
}

void ErrorExchange::setCode(eHttpStatusCode code)
{
	_code = code;
}

void ErrorExchange::setListen(const Listen &listen)
{
	*_listen = listen;
}

void ErrorExchange::setMessage(const std::string &message)
{
	_message = message;
}

void ErrorExchange::setFileToSend(const std::string &fileToSend)
{
	_fileToSend = fileToSend;
}
