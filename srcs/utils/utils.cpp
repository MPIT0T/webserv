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
	std::string errorPage = "<!DOCTYPE html>"
		"<html lang=\"fr\">"
		"<head>"
		"<meta charset=\"UTF-8\">"
		"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
		"<title>Error " + toString(code) + "</title>"
		"<style>"
		"h1 { font-size: 50px; }"
		"body { display: flex; justify-content: center; align-items: center; height: 100vh; font-family: 'Inter', sans-serif; background-color: #faeedc; }"
		"div { font-size: 2rem; font-weight: semibold; color: #281515; text-align: center; }"
		"</style>"
		"</head>"
		"<body>"
		"<div>"
		"<h1> Error : " + toString(code) + "</h1>"
		"</div>"
		"</body>"
		"</html>";
	return errorPage;
}
