#include "Route.hpp"

// Constructors

Route::Route(void) : _directory_listing(false), _path(""), _root(""), _http_redirect(""), _default_file("") , _allow_methods(), _cgi() {}

Route::Route(const Route &src) {
	*this = src;
}

Route &Route::operator=(const Route &src) {
	if (this != &src) {
		this->_directory_listing = src._directory_listing;
		this->_path = src._path;
		this->_root = src._root;
		this->_http_redirect = src._http_redirect;
		this->_allow_methods = src._allow_methods;
		this->_cgi = src._cgi;
		this->_default_file = src._default_file;
	}
	return *this;
}

Route::Route (std::string routeStr) {
	std::size_t pos = 0;
    if ((pos = routeStr.find("\"path\":")) != std::string::npos) {
        pos += 7;
        std::size_t end = routeStr.find('"', pos + 1);
        _path = routeStr.substr(pos + 1, end - pos - 1);
    }
	else
		_path = "";
    if ((pos = routeStr.find("\"root\":")) != std::string::npos) {
        pos += 7;
        std::size_t end = routeStr.find('"', pos + 1);
        _root = routeStr.substr(pos + 1, end - pos - 1);
    }
	else
		_root = "";
	if ((pos = routeStr.find("\"http_redirect\":")) != std::string::npos) {
		pos += 16;
		std::size_t end = routeStr.find('"', pos + 1);
		_http_redirect = routeStr.substr(pos + 1, end - pos - 1);
	}
	else
		_http_redirect = "";
	if ((pos = routeStr.find("\"directory_listing\":")) != std::string::npos) {
		pos += 20;
		std::size_t end = routeStr.find(',', pos + 1);
		std::string directory_listing = routeStr.substr(pos, end - pos);
		_directory_listing = directory_listing == "true" ? true : false;
	}
	else
		_directory_listing = false;
	
	_allow_methods["DELETE"] = false;
	_allow_methods["POST"] = false;
	_allow_methods["GET"] = false;
	if ((pos = routeStr.find("\"allow_methods\":")) != std::string::npos) {
		pos += 16;
		std::size_t end = routeStr.find(']', pos + 1);
		std::string methods = routeStr.substr(pos + 1, end - pos - 1);
		std::size_t method_pos = 0;
		while ((method_pos = methods.find('"', method_pos)) != std::string::npos) {
			std::size_t method_end = methods.find('"', method_pos + 1);
			std::string method = methods.substr(method_pos + 1, method_end - method_pos - 1);
			if (method != "GET"
				&& method != "POST"
				&& method != "DELETE")
				throw std::exception(); //TODO put a good exception
			_allow_methods[method] = true;
			method_pos = method_end + 1;
		}
	}
	if ((pos = routeStr.find("\"default_file\":")) != std::string::npos) {
		pos += 15;
		std::size_t end = routeStr.find('"', pos + 1);
		_default_file = routeStr.substr(pos + 1, end - pos - 1);
	}
	else
		_default_file = "";
	_cgi["extension"] = "";
	_cgi["path"] = "";
	_cgi["upload_dir"] = "";
	if ((pos = routeStr.find("\"cgi\":")) != std::string::npos) {
		pos += 6;
		std::size_t end = routeStr.find('}', pos + 1);
		std::string cgi_str = routeStr.substr(pos + 1, end - pos - 1);
		std::size_t cgi_pos = 0;
		while ((cgi_pos = cgi_str.find('"', cgi_pos)) != std::string::npos) {
			std::size_t cgi_key_end = cgi_str.find("\":", cgi_pos + 1);
			std::string cgi_key = cgi_str.substr(cgi_pos + 1, cgi_key_end - cgi_pos - 1);
			cgi_pos = cgi_str.find(':', cgi_key_end) + 1;
			std::size_t cgi_value_start = cgi_str.find('"', cgi_pos) + 1;
			std::size_t cgi_value_end = cgi_str.find('"', cgi_value_start);
			std::string cgi_value = cgi_str.substr(cgi_value_start, cgi_value_end - cgi_value_start);
			if (cgi_key != "extension"
				&& cgi_key != "path"
				&& cgi_key != "upload_dir")
				throw std::exception(); //TODO put a good exception
			_cgi[cgi_key] = cgi_value;
			cgi_pos = cgi_value_end + 1;
		}
	}
}

// Destructor

Route::~Route() {}

// Setters

void Route::setDirectoryListing(bool directory_listing) {
	_directory_listing = directory_listing;
}

void Route::setPath(const std::string &path) {
	_path = path;
}

void Route::setRoot(const std::string &root) {
	_root = root;
}

void Route::setHttpRedirect(const std::string &http_redirect) {
	_http_redirect = http_redirect;
}

void Route::setAllowMethods(const std::map<std::string, bool> &allow_methods) {
	_allow_methods = allow_methods;
}

void Route::setCgi(const std::map<std::string, std::string> &cgi) {
	_cgi = cgi;
}

// Getters

bool Route::getDirectoryListing() const {
	return _directory_listing;
}

std::string Route::getPath() const {
	return _path;
}

std::string Route::getRoot() const {
	return _root;
}

std::string Route::getHttpRedirect() const {
	return _http_redirect;
}

std::map<std::string, bool> Route::getAllowMethods() const {
	return _allow_methods;
}

std::map<std::string, std::string> Route::getCgi() const {
	return _cgi;
}
// Print method using printf

void Route::print_arg() const{
	printf("	Path: %s\n", _path.c_str());
	printf("	Root: %s\n", _root.c_str());
	printf("	Default file: %s\n", _default_file.c_str());
	printf("	HTTP Redirect: %s\n", _http_redirect.c_str());
	printf("	Directory Listing: %s\n", _directory_listing ? "true" : "false");
	printf("	Allow Methods: ");
	for (std::map<std::string, bool>::const_iterator it = _allow_methods.begin(); it != _allow_methods.end(); ++it) {
		printf("%s: %s, ", it->first.c_str(), it->second ? "true" : "false");
	}
	printf("\n	CGI: ");
	for (std::map<std::string, std::string>::const_iterator it = _cgi.begin(); it != _cgi.end(); ++it) {
		printf("%s: %s, ", it->first.c_str(), it->second.c_str());
	}
	printf("\n\n\n");
}
