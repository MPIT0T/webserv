//
// Created by gberthol on 11/18/24.
//

#include <unistd.h>
#include "CGI.hpp"
#include <cstdlib>
#include <sys/wait.h>

CGI::CGI(const std::string	&path) : _path(path)
{
}

CGI::CGI(const CGI &old)
{
	this->_path = old._path;
}

CGI::~CGI()
{

}

CGI &CGI::operator=(const CGI &old)
{
	this->_path = old._path;
	return *this;
}

void CGI::execCGI()
{
	pid_t	pid;
	int 	status;

	pid = fork();
	if (!pid)
	{
		if (access(_path.c_str(), X_OK) == 0)
			execve(_path.c_str(), _args, _env);
		free_all();
		return ;
	}
	waitpid(0, &status, 0);
}
