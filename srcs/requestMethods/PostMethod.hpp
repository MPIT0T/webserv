//
// Created by gberthol on 10/29/24.
//

#pragma once
#include <iostream>
#include <stdexcept>

class PostMethod
{
	public:
		PostMethod();
		PostMethod(const std::string &content);
		PostMethod(const PostMethod &old);
		~PostMethod();
		PostMethod &operator=(const PostMethod &old);

		void	createFile();

	const std::string &getFileName() const;
	const std::string &getContent() const;

	void setFileName(const std::string &fileName);
	void setContent(const std::string &content);

	class PostMethodFileOpenException : public std::exception
	{
		public :
			const char *what() const throw();
	};

private:
		std::string	_fileName;
		std::string	_content;
};
