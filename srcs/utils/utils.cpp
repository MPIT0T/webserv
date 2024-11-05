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

std::vector<std::string> tokenizeConfig(const std::string& config) 
{
    std::vector<std::string> tokens;
    std::istringstream stream(config);
    std::string line;
    
    while (std::getline(stream, line)) {
        std::string cleanLine;
        bool inComment = false;
        
        // Traverse the line, skip comments, and preserve indentation
        for (std::string::size_type i = 0; i < line.size(); ++i) {
            if (line[i] == '#' && !inComment) { // Start of a comment
                inComment = true;
                break;
            }
            // Add character if not in a comment
            cleanLine += line[i];
        }
        
        // Only add non-empty lines to tokens
        if (!cleanLine.empty()) {
            tokens.push_back(cleanLine);
        }
    }
    return tokens;
}



void printTokens(const std::vector<std::string>& tokens) {
    for (std::vector<std::string>::const_iterator it = tokens.begin(); it != tokens.end(); ++it) {
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
}

void printListen(const std::vector<Listen>& listen) {
    for (std::vector<Listen>::const_iterator it = listen.begin(); it != listen.end(); ++it) {
        std::cout << "Listen: " << std::endl;
        std::cout << "Host: " << it->getHost() << ":" << it->getPort() << std::endl;
        std::cout << "ServerName: " << it->getServerName() << std::endl;
        std::cout << "MaxBodySize: " << it->getMaxBodySize() << std::endl;
        std::cout << "ErrorPages: " << std::endl;
        std::map<int, std::string> errorPages = it->getErrorPages();
        for (std::map<int, std::string>::const_iterator it = errorPages.begin(); it != errorPages.end(); ++it) {
            std::cout << it->first << ": " << it->second << std::endl;
        }
        std::cout << "Route: " << std::endl;
        std::map<std::string, Route> routes = it->getRoutes();
    }
    std::cout << std::endl;
}