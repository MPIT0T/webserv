//
// Created by gberthol on 10/29/24.
//

#include "PostMethod.hpp"
#include<fstream>

PostMethod::PostMethod()
{

}

PostMethod::PostMethod(const std::string &fileName, const std::string &content)
{
	_fileName = fileName;
	_content = content;
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