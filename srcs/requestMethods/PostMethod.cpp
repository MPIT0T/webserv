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
	_content = content;

	std::cout << _content << std::endl;
	while (_content.find('+') != std::string::npos)
		_content.at(_content.find('+')) = ' ';
	if (_content.find('='))
		_content.erase(0, _content.find('=') + 1);
	if (_content.find('&'))
		_fileName = _content.substr(0, _content.find('&'));
	if (_content.find('='))
		_content.erase(0, _content.find('=') + 1);
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

	if (_fileName.empty())
		return ;
	file.open(_fileName.c_str());
	if (!file.is_open())
		throw PostMethodFileOpenException();
	file << _content;
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

const char *PostMethod::PostMethodFileOpenException::what() const throw()
{
	return ("Can't open/create the file.");
}