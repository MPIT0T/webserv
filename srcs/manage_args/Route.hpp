#ifndef ROUTE_HPP
#define ROUTE_HPP

#include <string>
#include <map>

class Route{
private:
	bool								_directory_listing;
	std::string 						_path;
	std::string							_root;
	std::string 						_http_redirect;
	std::map <std::string, bool> 		_allow_methods;
	std::map <std::string, std::string> _cgi;

public:
	// Constructors

	Route( void );
	Route( const Route &src );
	Route &operator=( const Route &src );
	
	// Destructor
	
	~Route();
	
	// Setters

	void setDirectoryListing(bool directory_listing);
	void setPath(const std::string &path);
	void setRoot(const std::string &root);
	void setHttpRedirect(const std::string &http_redirect);
	void setAllowMethods(const std::map<std::string, bool> &allow_methods);
	void setCgi(const std::map<std::string, std::string> &cgi);

	// Getters

	bool getDirectoryListing() const;
	std::string getPath() const;
	std::string getRoot() const;
	std::string getHttpRedirect() const;
	std::map<std::string, bool> getAllowMethods() const;
	std::map<std::string, std::string> getCgi() const;
};

#endif // Route_HPP