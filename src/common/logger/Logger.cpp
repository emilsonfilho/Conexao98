//
// Created by Emilson Filho on 11/03/2026.
//

#include "Logger.h"

#include <fstream>
#include <iostream>
#include <ostream>
#include <iomanip>
#include <ctime>

Logger::Logger() {
    logFile = std::ofstream("conexao98.log", std::ios_base::app);
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

Logger& Logger::getLogger() {
    static Logger instance;
    return instance;
}

std::string Logger::levelToString(const LogLevelEnum logLevel) {
    std::string logLevelString = "[";

    switch (logLevel) {
        case LogLevelEnum::DEBUG:
            logLevelString += "DEBUG";
            break;
        case LogLevelEnum::INFO:
            logLevelString += "INFO";
            break;
        case LogLevelEnum::ERR:
            logLevelString += "ERROR";
            break;
        case LogLevelEnum::WARNING:
            logLevelString += "WARNING";
            break;
        default:
            logLevelString += "UNKNOWN";
            break;
    }

    logLevelString += "]";

    return logLevelString;
}

std::string Logger::getCurrentTime() {
    std::ostringstream out;

    const auto currentTime = std::chrono::system_clock::now();

    const std::time_t ltime = std::chrono::system_clock::to_time_t(currentTime);
    tm timeinfo{};

    #ifdef _WIN32
        localtime_s(&timeinfo, &ltime);
    #else
        localtime_r(&ltime, &timeinfo);
    #endif

    out << std::put_time(&timeinfo, "[%Y-%m-%d %H:%M:%S]");

    return out.str();
}

void Logger::generalLog(const LogLevelEnum logLevel, const std::string &logMessage) {
    std::string log;
    log.reserve(1024);

    log += Logger::getCurrentTime();
    log += Logger::levelToString(logLevel);
    log += logMessage;
    log += '\n';

    std::lock_guard<std::mutex> logLock(logMutex);

    if (logFile.is_open()) {
        logFile << log;
    }
}

void Logger::info(const std::string &logMessage) {
    generalLog(LogLevelEnum::INFO, logMessage);
}

void Logger::warning(const std::string& logMessage) {
    generalLog(LogLevelEnum::WARNING, logMessage);
}

void Logger::error(const std::string &logMessage) {
    generalLog(LogLevelEnum::ERR, logMessage);
}

void Logger::debug(const std::string &logMessage) {
    generalLog(LogLevelEnum::DEBUG, logMessage);
}