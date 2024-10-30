#include "Route.hpp"

// Constructors

Route::Route(void) : _directory_listing(false), _path(""), _root(""), _http_redirect(""), _allow_methods(), _cgi() {}

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
	}
	return *this;
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