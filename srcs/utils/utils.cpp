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



void printTokens(const std::vector<std::string>& tokens) {
    for (std::vector<std::string>::const_iterator it = tokens.begin(); it != tokens.end(); ++it) {
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
}

// Fonction pour afficher les détails d'une route
void printRoute(const Route& route) {
    std::cout << "  Route:" << std::endl;
    std::cout << "    Path: " << route.getPath() << std::endl;
    std::cout << "    Root: " << route.getRoot() << std::endl;
    std::cout << "    Default File: " << route.getDefaultFile() << std::endl;
    std::cout << "    HTTP Redirect: " << route.getHttpRedirect() << std::endl;
    std::cout << "    Directory Listing: " << (route.getDirectoryListing() ? "true" : "false") << std::endl;

    std::cout << "    Allowed Methods: ";
    std::map<std::string, bool> methods = route.getAllowMethods();
    for (std::map<std::string, bool>::const_iterator it = methods.begin(); it != methods.end(); ++it) {
        if (it->second) {
            std::cout << it->first << " ";
        }
    }
    std::cout << std::endl;

    std::cout << "    CGI Settings:" << std::endl;
    std::map<std::string, std::string> cgi = route.getCgi();
    for (std::map<std::string, std::string>::const_iterator it = cgi.begin(); it != cgi.end(); ++it) {
        std::cout << "      " << it->first << ": " << it->second << std::endl;
    }
}

// Fonction pour afficher les détails d'un Listen
void printListen(const Listen& listen) {
    std::cout << "Listen Configuration:" << std::endl;
    std::cout << "  Port: " << listen.getPort() << std::endl;
    std::cout << "  Host: " << listen.getHost() << std::endl;
    std::cout << "  Server Name: " << listen.getServerName() << std::endl;
    std::cout << "  Max Body Size: " << listen.getMaxBodySize() << " bytes" << std::endl;

    std::cout << "  Error Pages:" << std::endl;
    std::map<int, std::string> errorPages = listen.getErrorPages();
    for (std::map<int, std::string>::const_iterator it = errorPages.begin(); it != errorPages.end(); ++it) {
        std::cout << "    " << it->first << ": " << it->second << std::endl;
    }

    std::cout << "  Routes:" << std::endl;
    std::map<std::string, Route> routes = listen.getRoutes();
    for (std::map<std::string, Route>::const_iterator it = routes.begin(); it != routes.end(); ++it) {
        printRoute(it->second);
    }
}

// Fonction pour afficher le vecteur de Listen
void printListenVector(const std::vector<Listen>& listenConfigs) {
    for (std::vector<Listen>::const_iterator it = listenConfigs.begin(); it != listenConfigs.end(); it++) {
        printListen(*it);
    }
}

