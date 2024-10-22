//
// Created by gberthol on 10/21/24.
//

#include "Header.hpp"

Header::Header()
{
}

const std::string &Header::getType() const
{
	return type;
}

const std::string &Header::getAttribute() const
{
	return attribute;
}

void Header::setType(const std::string &_type)
{
	Header::type = _type;
}

void Header::setAttribute(const std::string &_attribute)
{
	Header::attribute = _attribute;
}

Header::Header(const Header &old)
{
	this->attribute = old.attribute;
	this->type = old.type;
}

Header::~Header()
{
}

Header &Header::operator=(const Header &old)
{
	this->attribute = old.attribute;
	this->type = old.type;
	return *this;
}


