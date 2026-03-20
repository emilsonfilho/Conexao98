//
// Created by Emilson Filho on 11/03/2026.
//

#ifndef CONEXAO98_LOGGER_H
#define CONEXAO98_LOGGER_H

#include <mutex>
#include <string>
#include <fstream>

#include "LogLevel.h"

class Logger {
private:
    std::mutex logMutex;
    std::ofstream logFile;

    Logger();
    ~Logger();

    static std::string levelToString(LogLevelEnum logLevel);
    static std::string getCurrentTime();

    void generalLog(LogLevelEnum logLevel, const std::string &logMessage);
public:
    static Logger &getLogger();

    void debug(const std::string& logMessage);
    void info(const std::string& logMessage);
    void warning(const std::string& logMessage);
    void error(const std::string& logMessage);
};


#endif //CONEXAO98_LOGGER_H