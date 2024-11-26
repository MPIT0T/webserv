//
// Created by gberthol on 11/18/24.
//

#pragma once

#include <iostream>

class CGI
{
	public:
		CGI(const std::string &path);
		CGI(const CGI &old);
		~CGI();
		CGI &operator=(const CGI &old);

		void	execCGI();

	private:
		std::string		_path;
		char			**_args;
		char			**_env;
};
