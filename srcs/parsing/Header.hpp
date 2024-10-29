//
// Created by gberthol on 10/21/24.
//

#pragma once
#include <iostream>

class Header
{
	public:
		Header();
		Header(const Header &old);
		~Header();
		Header &operator=(const Header &old);

		const std::string &getType() const;
		const std::string &getAttribute() const;

		void setType(const std::string &_type);
		void setAttribute(const std::string &_attribute);

private:
		std::string	type;
		std::string	attribute;
};
