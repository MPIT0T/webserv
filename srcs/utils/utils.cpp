#include "utils.hpp"

std::string readFileContent(const std::string& filePath) {
	std::ifstream file(filePath.c_str());
	if (!file.is_open()) {
		throw std::runtime_error("Unable to open file: " + filePath);
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}


std::string toString(int number) {
	std::stringstream ss;
	ss << number;
	return ss.str();
}


std::string errorPage(int code) {
	std::string errorPage = "<html><head><title>Error</title></head><body><h1>Error " + toString(code) + "</h1></body></html>";
	return errorPage;
}
