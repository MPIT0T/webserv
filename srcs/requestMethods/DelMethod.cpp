//
// Created by gberthol on 12/16/24.
//

#include "DelMethod.hpp"
#include <cstdio>

DelMethod::DelMethod(const std::string &fileName) : _fileName(fileName)
{
	_code = OK;
}

DelMethod::DelMethod(const DelMethod &old)
{
	_fileName = old._fileName;
}

DelMethod::~DelMethod()
{
}

DelMethod &DelMethod::operator=(const DelMethod &old)
{
	this->_fileName = old._fileName;
	return *this;
}

void DelMethod::deleteFile()
{
	if (!std::remove(_fileName.c_str()))
	{
		_message = "<!DOCTYPE html>\n"
				   "<html lang=\"fr\">\n"
				   "<head>\n"
				   "    <meta charset=\"UTF-8\">\n"
				   "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
				   "    <title>404 Not Found</title>\n"
				   "\n"
				   "    <style>\n"
				   "        h1 {\n"
				   "            font-size: 50px;\n"
				   "        }\n"
				   "        p {\n"
				   "            font-size: 20px;\n"
				   "        }\n"
				   "        a {\n"
				   "            color: #007BFF;\n"
				   "            text-decoration: none;\n"
				   "        }\n"
				   "        a:hover {\n"
				   "            text-decoration: underline;\n"
				   "        }\n"
				   "\n"
				   "        .container{\n"
				   "\t\t\t--max-width: 1000px;\n"
				   "\t\t\t--padding: 1rem;\n"
				   "\n"
				   "\t\t\twidth: min(var(--max-width), 100% - (var(--padding) * 1.2));\n"
				   "\t\t\tmargin-inline: auto;\n"
				   "\t\t}\n"
				   "\t\tbody {\n"
				   "\t\t\tdisplay: flex;\n"
				   "\t\t\tjustify-content: center;\n"
				   "\t\t\talign-items: center;\n"
				   "\t\t\theight: 100vh;\n"
				   "\t\t\tfont-family: 'Inter', sans-serif;\n"
				   "\t\t\tbackground-color: #faeedc;\n"
				   "            \n"
				   "\t\t}\n"
				   "\t\tdiv {\n"
				   "\t\t\tfont-size: 2rem;\n"
				   "\t\t\tfont-weight: semibold;\n"
				   "\t\t\tcolor: #281515;\n"
				   "\t\t\ttext-align: center;\n"
				   "\t\t}\n"
				   "\n"
				   "    </style>\n"
				   "    </head>\n"
				   "<body>\n"
				   "  <div>\n"
				   "    <h1>file: " + _fileName +
				   "</h1>\n"
				   "    <p> has been deleted successfully.</p>\n"
				   "    <p><a href=\"/\">Go back to the homepage</a></p>\n"
				   "  </div>\n"
				   "    </body>\n"
				   "</html>";
	}
	else
		_code = UNAUTHORIZED;
}

const std::string &DelMethod::getMessage() const
{
	return _message;
}

eHttpStatusCode DelMethod::getCode() const
{
	return _code;
}
