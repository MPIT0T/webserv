//
// Created by gberthol on 10/22/24.
//

#include "SendResponse.hpp"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <map>
#include <iostream>
#include <ctime>


static std::string getTimeFormat()
{
	time_t			result = time(0);
	std::string		tmp;
	std::string		tmp1;
	std::string		tmp2;
	std::string		resultStr;

	resultStr = asctime(gmtime(&result));
	tmp = resultStr.substr(0, resultStr.find(' '));
	resultStr.erase(0, resultStr.find(' '));
	tmp1 = resultStr.substr(0, resultStr.find(' ', 1));
	resultStr.erase(0, resultStr.find(' ', 1));
	tmp2 = resultStr.substr(0, resultStr.find(' ', 1));
	resultStr.erase(0, resultStr.find(' ', 1));
	tmp1.append(resultStr);
	tmp2.append(tmp1);
	tmp.push_back(',');
	tmp.append(tmp2);
	resultStr = tmp;
	resultStr.erase(resultStr.size() - 1, resultStr.size());
	tmp = resultStr.substr(resultStr.size() - 5, resultStr.size());
	resultStr.erase(resultStr.size() - 5, resultStr.size());
	tmp1 = resultStr.substr(resultStr.size() - 9, resultStr.size());
	resultStr.erase(resultStr.size() - 9, resultStr.size());
	resultStr.append(tmp);
	resultStr.append(tmp1);
	resultStr.append(" GMT\n");
	return resultStr;
}

std::string ft_itoa(unsigned int nbr)
{
	std::string		result;
	unsigned int	divide = 1;

	for (; nbr / divide >= 10; divide *= 10);
	for (; divide > 0; divide /= 10)
		result.push_back( (nbr / divide) % 10 + '0');
	return result;
}

SendResponse::SendResponse()
{
	code = SERVICE_UNAVAILABLE;
}

SendResponse::SendResponse(const SendResponse &old)
{
	this->message = old.message;
}

SendResponse &SendResponse::operator=(const SendResponse &old)
{
	this->message = old.message;
	return *this;
}

SendResponse::~SendResponse()
{
}

void SendResponse::getNewMessage()
{
	int				fd = open(fileToSend.c_str(), O_RDONLY);
	char			tab[1024];
	size_t 			nbrRead = 1;
	struct 	stat	messageStat;

	//clear old message
	message.clear();

	//get http version
	message = version;

	if (fd <= 0 || stat(fileToSend.c_str(), &messageStat) < 0)
		code = INTERNAL_SERVER_ERROR;

	//get http response status
	message.push_back(' ');
	message.append(ft_itoa((unsigned  int)code)); // TODO save myself from satan
	message.push_back(' ');
	message.append(getStatusDescription(code));

	//get time format
	message.append("\nDate: ");
	message.append(getTimeFormat());

	//get serveur
	message.append("Server: ");
	message.append(serverName);
		message.push_back('\n');

	//get content type
	message.append("Content-Type: ");
	message.append(contentType);

	//get message length
	message.append("\nContent-Length: ");
	if (code != INTERNAL_SERVER_ERROR && messageStat.st_size)
		message.append(ft_itoa(messageStat.st_size));

	//get connection
	message.append("\nConnection: ");
	message.append(connection);

	//get message body
	message.append("\n\n");
	if (fd <= 0 || stat(fileToSend.c_str(), &messageStat) < 0)
	{
		message.append("<!DOCTYPE html>\n\n<head>\n<title>ERROR</title>\n</head>\n\n<body>\n<h1>error 500, INTERNAL_SERVER_ERROR</h1>\n</body>");
		return		;
	}
	// std::cout << "message: " << message << std::endl; // TODO satan might be here
	write(fdClient, message.c_str(), message.size());
	while (nbrRead > 0)
	{
		nbrRead = read(fd, tab, 1023);
		tab[nbrRead] = 0;
		write(fdClient, tab, nbrRead);
	}
	close(fd);
	return ;
}

const std::string &SendResponse::getMessage() const
{
	return message;
}

SendResponse::SendResponse(const std::string &_version,
						   const std::string &_connection,
						   const std::string &_serverName,
						   const std::string &_contentType,
						   const std::string &_fileToSend,
						   eHttpStatusCode _code, int _fdClient)
{
	version = _version;
	connection = _connection;
	serverName = _serverName;
	fileToSend = _fileToSend;
	code = _code;
	fdClient = _fdClient;

	contentType = mimeTypeOfFile(fileToSend.substr(fileToSend.find_last_of('.'), fileToSend.size()));
	if (_contentType.find(contentType) == std::string::npos)
	{
		std::cout << "error: " << contentType << std::endl;
		std::cout << _contentType << std::endl;
	}
}

std::string getStatusDescription(eHttpStatusCode code)
{
	std::map<eHttpStatusCode, std::string> statusDescriptions;

	statusDescriptions.insert(std::make_pair(CONTINUE, "Continue"));
	statusDescriptions.insert(std::make_pair(SWITCHING_PROTOCOLS, "Switching Protocols"));
	statusDescriptions.insert(std::make_pair(PROCESSING, "Processing"));
	statusDescriptions.insert(std::make_pair(OK, "OK"));
	statusDescriptions.insert(std::make_pair(CREATED, "Created"));
	statusDescriptions.insert(std::make_pair(ACCEPTED, "Accepted"));
	statusDescriptions.insert(std::make_pair(NON_AUTHORITATIVE_INFORMATION, "Non-Authoritative Information"));
	statusDescriptions.insert(std::make_pair(NO_CONTENT, "No Content"));
	statusDescriptions.insert(std::make_pair(RESET_CONTENT, "Reset Content"));
	statusDescriptions.insert(std::make_pair(PARTIAL_CONTENT, "Partial Content"));
	statusDescriptions.insert(std::make_pair(MULTIPLE_CHOICES, "Multiple Choices"));
	statusDescriptions.insert(std::make_pair(MOVED_PERMANENTLY, "Moved Permanently"));
	statusDescriptions.insert(std::make_pair(FOUND, "Found"));
	statusDescriptions.insert(std::make_pair(SEE_OTHER, "See Other"));
	statusDescriptions.insert(std::make_pair(NOT_MODIFIED, "Not Modified"));
	statusDescriptions.insert(std::make_pair(TEMPORARY_REDIRECT, "Temporary Redirect"));
	statusDescriptions.insert(std::make_pair(PERMANENT_REDIRECT, "Permanent Redirect"));
	statusDescriptions.insert(std::make_pair(BAD_REQUEST, "Bad Request"));
	statusDescriptions.insert(std::make_pair(UNAUTHORIZED, "Unauthorized"));
	statusDescriptions.insert(std::make_pair(PAYMENT_REQUIRED, "Payment Required"));
	statusDescriptions.insert(std::make_pair(FORBIDDEN, "Forbidden"));
	statusDescriptions.insert(std::make_pair(NOT_FOUND, "Not Found"));
	statusDescriptions.insert(std::make_pair(METHOD_NOT_ALLOWED, "Method Not Allowed"));
	statusDescriptions.insert(std::make_pair(NOT_ACCEPTABLE, "Not Acceptable"));
	statusDescriptions.insert(std::make_pair(REQUEST_TIMEOUT, "Request Timeout"));
	statusDescriptions.insert(std::make_pair(CONFLICT, "Conflict"));
	statusDescriptions.insert(std::make_pair(GONE, "Gone"));
	statusDescriptions.insert(std::make_pair(LENGTH_REQUIRED, "Length Required"));
	statusDescriptions.insert(std::make_pair(PAYLOAD_TOO_LARGE, "Payload Too Large"));
	statusDescriptions.insert(std::make_pair(URI_TOO_LONG, "URI Too Long"));
	statusDescriptions.insert(std::make_pair(UNSUPPORTED_MEDIA_TYPE, "Unsupported Media Type"));
	statusDescriptions.insert(std::make_pair(RANGE_NOT_SATISFIABLE, "Range Not Satisfiable"));
	statusDescriptions.insert(std::make_pair(EXPECTATION_FAILED, "Expectation Failed"));
	statusDescriptions.insert(std::make_pair(TOO_MANY_REQUESTS, "Too Many Requests"));
	statusDescriptions.insert(std::make_pair(INTERNAL_SERVER_ERROR, "Internal Server Error"));
	statusDescriptions.insert(std::make_pair(NOT_IMPLEMENTED, "Not Implemented"));
	statusDescriptions.insert(std::make_pair(BAD_GATEWAY, "Bad Gateway"));
	statusDescriptions.insert(std::make_pair(SERVICE_UNAVAILABLE, "Service Unavailable"));
	statusDescriptions.insert(std::make_pair(GATEWAY_TIMEOUT, "Gateway Timeout"));
	statusDescriptions.insert(std::make_pair(HTTP_VERSION_NOT_SUPPORTED, "HTTP Version Not Supported"));
	statusDescriptions.insert(std::make_pair(INSUFFICIENT_STORAGE, "Insufficient Storage"));

	return statusDescriptions[code];
}

std::string mimeTypeOfFile(std::string fileToSend)
{
	std::map<std::string, std::string> mimeTypes;

	mimeTypes[".html"] = "text/html";
	mimeTypes[".htm"] = "text/html";
	mimeTypes[".css"] = "text/css";
	mimeTypes[".js"] = "application/javascript";
	mimeTypes[".json"] = "application/json";
	mimeTypes[".xml"] = "application/xml";
	mimeTypes[".jpg"] = "image/jpeg";
	mimeTypes[".jpeg"] = "image/jpeg";
	mimeTypes[".png"] = "image/png";
	mimeTypes[".gif"] = "image/gif";
	mimeTypes[".bmp"] = "image/bmp";
	mimeTypes[".ico"] = "image/x-icon";
	mimeTypes[".svg"] = "image/svg+xml";
	mimeTypes[".webp"] = "image/webp";
	mimeTypes[".tiff"] = "image/tiff";
	mimeTypes[".tif"] = "image/tiff";
	mimeTypes[".pdf"] = "application/pdf";
	mimeTypes[".zip"] = "application/zip";
	mimeTypes[".tar"] = "application/x-tar";
	mimeTypes[".gz"] = "application/gzip";
	mimeTypes[".rar"] = "application/vnd.rar";
	mimeTypes[".7z"] = "application/x-7z-compressed";
	mimeTypes[".txt"] = "text/plain";
	mimeTypes[".csv"] = "text/csv";
	mimeTypes[".mp3"] = "audio/mpeg";
	mimeTypes[".wav"] = "audio/wav";
	mimeTypes[".ogg"] = "audio/ogg";
	mimeTypes[".mp4"] = "video/mp4";
	mimeTypes[".m4v"] = "video/x-m4v";
	mimeTypes[".mov"] = "video/quicktime";
	mimeTypes[".avi"] = "video/x-msvideo";
	mimeTypes[".flv"] = "video/x-flv";
	mimeTypes[".mkv"] = "video/x-matroska";
	mimeTypes[".webm"] = "video/webm";
	mimeTypes[".woff"] = "font/woff";
	mimeTypes[".woff2"] = "font/woff2";
	mimeTypes[".ttf"] = "font/ttf";
	mimeTypes[".otf"] = "font/otf";
	mimeTypes[".eot"] = "application/vnd.ms-fontobject";
	mimeTypes[".wasm"] = "application/wasm";
	mimeTypes[".md"] = "text/markdown";
	mimeTypes[".yaml"] = "application/x-yaml";
	mimeTypes[".yml"] = "application/x-yaml";
	return (mimeTypes[fileToSend]);
}