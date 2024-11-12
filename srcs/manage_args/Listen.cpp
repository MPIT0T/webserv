#include "Listen.hpp"

// Constructors
Listen::Listen(void) : _port(0), _maxBodySize(0), _host(""), _serverName("") {}

Listen::Listen(const Listen &src) {
	*this = src;
}

Listen &Listen::operator=(const Listen &src) {
	if (this != &src) {
		this->_port = src._port;
		this->_maxBodySize = src._maxBodySize;
		this->_host = src._host;
		this->_serverName = src._serverName;
		this->_errorPages = src._errorPages;
		this->_routes = src._routes;
	}
	return *this;
}


Listen::Listen(std::string content)
{
	// Manual parsing for demonstration. Not a robust JSON parser.
    
    // Parse basic fields like port, host, server_name, etc.
    std::size_t pos = 0;
    if ((pos = content.find("\"port\":")) != std::string::npos) {
        pos += 7;  // Move past "port": 
        _port = std::atoi(content.c_str() + pos);
    }
    if ((pos = content.find("\"host\":")) != std::string::npos) {
        pos += 7;
        std::size_t end = content.find('"', pos + 1);
        _host = content.substr(pos + 1, end - pos - 1);
    }
    if ((pos = content.find("\"server_name\":")) != std::string::npos) {
        pos += 14;
        std::size_t end = content.find('"', pos + 1);
        _serverName = content.substr(pos + 1, end - pos - 1);
    }
    if ((pos = content.find("\"client_max_body_size\":")) != std::string::npos) {
        pos += 23;
        std::size_t end = content.find('"', pos + 1);
        std::string bodySizeStr = content.substr(pos + 1, end - pos - 1);
        _maxBodySize = parseSize(bodySizeStr);
    }

    // Parse error pages
    if ((pos = content.find("\"error_pages\":")) != std::string::npos) {
        pos += 14;
        std::size_t end = content.find('}', pos);
        std::string errorPagesStr = content.substr(pos, end - pos);
        parseErrorPages(errorPagesStr);

	}
		
    // Parse routes
    if ((pos = content.find("\"routes\":")) != std::string::npos) {
        pos += 9;
        std::size_t end = content.find(']', pos);
        std::string routesStr = content.substr(pos, end - pos);
        parseRoutes(routesStr);
    }

	print_value();
}

// Destructor
Listen::~Listen() {}

// Setters
void Listen::setPort(int port) {
	_port = port;
}

void Listen::setMaxBodySize(int maxBodySize) {
	_maxBodySize = maxBodySize;
}

void Listen::setHost(std::string host) {
	_host = host;
}

void Listen::setServerName(std::string serverName) {
	_serverName = serverName;
}

void Listen::setErrorPages(std::map<int, std::string> errorPages) {
	_errorPages = errorPages;
}

void Listen::setRoutes(std::vector<Route> routes) {
	_routes.clear();
	for (size_t i = 0; i < routes.size(); ++i) {
		_routes[routes[i].getPath()] = routes[i];
	}
}

// Getters
int Listen::getPort(void) const {
	return _port;
}

int Listen::getMaxBodySize(void) const {
	return _maxBodySize;
}

std::string Listen::getHost(void) const {
	return _host;
}

std::string Listen::getServerName(void) const {
	return _serverName;
}

std::map<int, std::string> Listen::getErrorPages(void) const {
	return _errorPages;
}

std::map<std::string, Route> Listen::getRoutes(void) const {
	return _routes;
}


void Listen::parseRoutes(const std::string &routesStr) {
    std::size_t pos = 0;
    
    while ((pos = routesStr.find("{", pos)) != std::string::npos) {
        // Find the closing brace for this route block
        std::size_t end = routesStr.find("}", pos);
        if (end == std::string::npos) {
            // Break if there's no matching closing brace
            break;
        }

        // Extract the route string
        std::string routeStr = routesStr.substr(pos, end - pos + 1);
        
        // Create and parse the Route object with routeStr
        Route route(routeStr);
        _routes[route.getPath()] = route;

        // Move pos to just after this route's closing brace to find the next one
        pos = end + 1;
    }
}

int Listen::parseSize(const std::string &sizeStr) {
    int size = 0;
    if (sizeStr.find("M") != std::string::npos) {
        size = std::atoi(sizeStr.c_str()) * 1024 * 1024;
    } else if (sizeStr.find("K") != std::string::npos) {
        size = std::atoi(sizeStr.c_str()) * 1024;
    } else {
        size = std::atoi(sizeStr.c_str());
    }
    return size;
}

void Listen::parseErrorPages(const std::string &errorPagesStr) {
    std::size_t pos = 0;
    while ((pos = errorPagesStr.find('"', pos)) != std::string::npos) {
        // Move to the start of the number after the quote
        pos++;
        std::size_t codeEnd = errorPagesStr.find('"', pos);
        if (codeEnd == std::string::npos) break;
        
        int errorCode = std::atoi(errorPagesStr.substr(pos, codeEnd - pos).c_str());
        
        // Find the start of the error page path (the next quoted section)
        pos = errorPagesStr.find('"', codeEnd + 1);
        if (pos == std::string::npos) break;
        
        std::size_t pathEnd = errorPagesStr.find('"', pos + 1);
        if (pathEnd == std::string::npos) break;

        std::string errorPage = errorPagesStr.substr(pos + 1, pathEnd - pos - 1);
        
        // Store the parsed error code and page in the map
        _errorPages[errorCode] = errorPage;

        // Move `pos` past the current path end to continue parsing
        pos = pathEnd + 1;
    }
}

void Listen::print_value(){
	printf("Port: %d\n", _port);
	printf("Max Body Size: %d\n", _maxBodySize);
	printf("Host: %s\n", _host.c_str());
	printf("Server Name: %s\n", _serverName.c_str());

	printf("Error Pages:\n");
	for (std::map<int, std::string>::const_iterator it = _errorPages.begin(); it != _errorPages.end(); ++it) {
		printf("  %d: %s\n", it->first, it->second.c_str());
	}

	printf("Routes:\n");
	for (std::map<std::string, Route>::const_iterator it = _routes.begin(); it != _routes.end(); ++it) {
		printf("  Path: %s\n", it->first.c_str());
		// Assuming Route class has a print method or similar to display its content
		it->second.print_arg();
	}
}