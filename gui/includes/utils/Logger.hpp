/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** vim on top !
*/

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <sys/time.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <mutex>

#define LOGFILE "debug/debug.log"
#define LOG(...) logger.Log(__VA_ARGS__)

// Log levels
enum LogLevel { I, W, E };

class Logger
{
    private:
        std::vector<std::string> logLines;
        std::mutex logMutex;

        static void initialize()
        {
            std::ofstream logFile(LOGFILE, std::ios_base::trunc);
            logFile.close();
        }

        static std::string
        CurrentDateTime()
        {
            struct timeval tv;
            gettimeofday(&tv, nullptr);

            time_t now = tv.tv_sec;
            tm *ltm = localtime(&now);

            char buffer[30];
            int milliseconds = tv.tv_usec / 1000;
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);

            char currentTime[40];
            snprintf(currentTime, sizeof(currentTime), "%s:%03d", buffer, milliseconds);

            return std::string(currentTime);
        }

    public:
        Logger() { initialize(); };
        ~Logger() = default;

        // class methods
        std::vector<std::string>& getLogLines() {
            return logLines;
        }

        void Log(const std::string &message, LogLevel level = I)
        {
            std::lock_guard<std::mutex> guard(logMutex);
            std::ofstream logFile(LOGFILE, std::ios_base::app);

            if (logFile.is_open()) {
                std::string levelStr;
                switch (level) {
                case I:
                    levelStr = "INFO";
                    break;
                case W:
                    levelStr = "WARNING";
                    break;
                case E:
                    levelStr = "ERROR";
                    break;
                }

                std::string logMessage = "[" + CurrentDateTime() + "] [" + levelStr + "] " + message;
                logFile << logMessage << std::endl;
                logFile.close();

                logLines.push_back(logMessage);
            }
        }
}; // class Logger

extern Logger logger; // global logger pre-declaration

#endif // LOGGER_HPP
