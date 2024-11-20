#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <map>
#include <string>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctime>
#include <vector>
#include <cstdio>
#include <cerrno>
#include <cstring>
#include <cstdlib>

class Logger
{
private:
	static bool _logState;
	static bool _logFileState;
	static bool _logDebugState;
	static std::string _logFileNameTermination;
	static std::string _path;
public:
	/* ENUMs */
	enum LogLevel
	{
		FATAL = 0,
		ERROR,
		WARNING,
		INFO,
		TRACE,
		DEBUG,
	};
	// logInstance
	Logger();
	Logger( char **envp );
	Logger(const Logger &src);
	Logger &operator=(const Logger &src);
	
	~Logger();

	/* MAIN */
	static void log(LogLevel level, const char *msg, ...);

	/* SETTERS */
	static void setLogState(bool state);
	static void setLogFileState(bool state);
	static void setLogDebugState(bool state);

	/* GETTERS */
	static bool getLogState(void);
	static bool getLogFileState(void);
	static bool getLogDebugState(void);
	static std::string getLogFileNameTermination(void);
	static std::string getLogLevelStr(LogLevel level);
	static std::string getLogLevelColor(LogLevel level);

	/* CLEANUP */
	// static void cleanup(void);

};

#endif // LOGGER_HPP
