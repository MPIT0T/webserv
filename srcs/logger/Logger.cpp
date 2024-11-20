#include "Logger.hpp"

bool Logger::_logState = true;
bool Logger::_logFileState = true;
bool Logger::_logDebugState = false;
std::string Logger::_logFileNameTermination = ".log";

std::string Logger::_path = "";

Logger::Logger()
{
}

Logger::Logger( char **envp )
{
    if (envp)
    {
        for (int i = 0; envp[i]; i++)
        {
            std::string env = envp[i];
            if (env.find("PWD=") != std::string::npos)
            {
                _path = env.substr(4);
                break;
            }
        }
    }
    else
    {
        _path = "";
    }
}

Logger::Logger(const Logger &src)
{
    *this = src;
}

Logger &Logger::operator=(const Logger &src)
{
    if (this != &src)
    {
        _logState = src._logState;
        _logFileState = src._logFileState;
        _logDebugState = src._logDebugState;
        _logFileNameTermination = src._logFileNameTermination;
    }
    return *this;
}

Logger::~Logger()
{
}

void Logger::log(LogLevel level, const char *msg, ...)
{
    if (!_logState)
        return;

    va_list args;
    va_start(args, msg);

    std::string logLevelStr = getLogLevelStr(level);
    std::string logLevelColor = getLogLevelColor(level);

    // Get current time
    std::time_t now = std::time(NULL);
    char timeStr[20];
    std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

    std::cout << logLevelColor << "[" << timeStr << "] [" << logLevelStr << "] " << msg << "\033[0m" << std::endl;

    if (_logFileState)
    {
        char dateStr[11];
        std::strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", std::localtime(&now));
        std::string fileName = _path + "/log/" + std::string(dateStr) + _logFileNameTermination;
        FILE *file = fopen(fileName.c_str(), "a");
        if (file)
        {
            fprintf(file, "[%s] [%s] ", timeStr, logLevelStr.c_str());
            vfprintf(file, msg, args);
            fprintf(file, "\n");
            fclose(file);
        }
    }

    va_end(args);
}

void Logger::setLogState(bool state)
{
    _logState = state;
}

void Logger::setLogFileState(bool state)
{
    _logFileState = state;
}

void Logger::setLogDebugState(bool state)
{
    _logDebugState = state;
}

bool Logger::getLogState(void)
{
    return _logState;
}

bool Logger::getLogFileState(void)
{
    return _logFileState;
}

bool Logger::getLogDebugState(void)
{
    return _logDebugState;
}

std::string Logger::getLogFileNameTermination(void)
{
    return _logFileNameTermination;
}

std::string Logger::getLogLevelStr(LogLevel level)
{
    switch (level)
    {
    case FATAL:
        return "FATAL";
    case ERROR:
        return "ERROR";
    case WARNING:
        return "WARNING";
    case INFO:
        return "INFO";
    case TRACE:
        return "TRACE";
    case DEBUG:
        return "DEBUG";
    default:
        return "UNKNOWN";
    }
}

std::string Logger::getLogLevelColor(LogLevel level)
{
    switch (level)
    {
    case FATAL:
        return "\033[1;31m";
    case ERROR:
        return "\033[0;31m";
    case WARNING:
        return "\033[0;33m";
    case INFO:
        return "\033[0;32m";
    case TRACE:
        return "\033[0;34m";
    case DEBUG:
        return "\033[0;36m";
    default:
        return "\033[0m";
    }
}