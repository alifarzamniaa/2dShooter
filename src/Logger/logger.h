#ifndef LOGGER_H
#define LOGGER_H
#include <string>

// TODO(ali-farzamnia) : consider adding log level so you eliminate the logs you
// dont need
class Logger
{
    // TODO(ali-farzamnia) : if you ever want to do multi-threrading consider
    // taking action for std::cout in this class
  public:
    static void Warn(const std::string& msg);
    static void Error(const std::string& msg);
    static void Info(const std::string& msg);

  private:
    static void printTextWithColor(int in_colorCode,
                                   const std::string& in_text);
    static std::string GetTime();
};
#endif