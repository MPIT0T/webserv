//
// Created by gberthol on 12/16/24.
//


#pragma once

#include <iostream>
#include "utilsExchange.hpp"

class DelMethod
{
	public:
		DelMethod(const std::string &fileName);
		DelMethod(const DelMethod &old);
		~DelMethod();

		DelMethod &operator=(const DelMethod &old);

		void deleteFile();

	const std::string &getMessage() const;

	eHttpStatusCode getCode() const;

private:
		std::string			_fileName;
		std::string 		_message;
		eHttpStatusCode		_code;

};
