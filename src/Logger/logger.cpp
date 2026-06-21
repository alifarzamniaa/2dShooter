#include "logger.h"
#include <ctime>
#include <iostream>

enum class ColorCode
{
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34
};

std::string Logger::GetTime()
{
    // TODO(ali-farzamnia) : localtime_s seems to be for windows and for linux
    // and mac use localtime_r
    std::time_t currentTime = time(nullptr);
    struct std::tm date;
    #ifdef WIN_32
        localtime_s(&date, &currentTime);
    #else
        localtime_r(&currentTime,&date);
    #endif
    char buffer[50]; // to store the time
    std::strftime(buffer, sizeof(buffer), "[%Y-%B-%d --- %H:%M:%S]", &date);
    return buffer;
}

void Logger::printTextWithColor(int in_colorCode, const std::string& in_text)
{
    std::cout << "\33[" << in_colorCode << "m" << GetTime() << " " << in_text
              << "\n\33[37m";
}

void Logger::Warn(const std::string& msg)
{
    Logger::printTextWithColor(static_cast<int>(ColorCode::Yellow), msg);
}

void Logger::Info(const std::string& msg)
{
    Logger::printTextWithColor(static_cast<int>(ColorCode::Blue), msg);
}

void Logger::Error(const std::string& msg)
{
    Logger::printTextWithColor(static_cast<int>(ColorCode::Red), msg);
}