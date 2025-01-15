//
// Created by gberthol on 10/29/24.
//

#include "PostMethod.hpp"
#include<fstream>

PostMethod::PostMethod()
{

}

PostMethod::PostMethod(const std::string &content)
{
	if (content.find("filename=") == std::string::npos || content.find("&content=") == std::string::npos)
		return ;
	std::cout << content << std::endl;
	_fileName = content.substr(content.find("filename=") + 9, content.find('&') - (content.find("filename=") + 9));
	_content = content.substr(content.find("content=") + 8,  content.size() - content.find("content=") + 8);
	_content = _content.substr(0, _content.size() - 2);
	_fileName = "www/saved_files/" + _fileName;
}

PostMethod::PostMethod(const PostMethod &old)
{
	this->_fileName = old._fileName;
	this->_content = old._content;
}

PostMethod::~PostMethod()
{

}

PostMethod &PostMethod::operator=(const PostMethod &old)
{
	this->_fileName = old._fileName;
	this->_content = old._content;
	return *this;
}

void PostMethod::createFile()
{
	std::ofstream	file;
	std::string		tmp;

	if (_fileName.empty())
		return ;
	file.open(_fileName.c_str());
	if (!file.is_open())
		throw PostMethodFileOpenException();
	file << _content;
	tmp = _fileName.substr(_fileName.find("www/saved_files/") + 16, _fileName.size());
	_message = "file: " + tmp + " has been created correctly";
	_code = CREATED;
	file.close();
}

const std::string &PostMethod::getFileName() const
{
	return _fileName;
}

const std::string &PostMethod::getContent() const
{
	return _content;
}

void PostMethod::setFileName(const std::string &fileName)
{
	_fileName = fileName;
}

void PostMethod::setContent(const std::string &content)
{
	_content = content;
}

const std::string &PostMethod::getMessage() const
{
	return _message;
}

const eHttpStatusCode &PostMethod::getCode() const
{
	return _code;
}

const char *PostMethod::PostMethodFileOpenException::what() const throw()
{
	return ("Can't open/create the file.");
}