#include "Logger.hpp"

bool Logger::_logState = true;
bool Logger::_logFileState = false;
bool Logger::_logDebugState = false;
std::string Logger::_logFileName = "logfile.log";

#include <ctime>

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
        FILE *file = fopen(_logFileName.c_str(), "a");
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

std::string Logger::getLogFileName(void)
{
    return _logFileName;
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