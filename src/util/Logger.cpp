#include "Logger.h"
using namespace std;

namespace NauLib {
  const string Logger::RED = "";
  const string Logger::GREEN = "";
  const string Logger::YELLOW = "";
  const string Logger::WHITE = "";

  void Logger::logMessage(string message, string color) {
    printf("%s%s\n", color.c_str(), message.c_str());
  }

  void Logger::info(string message) {
    Logger::logMessage(string("[Info] - ").append(message), GREEN);
  }

  void Logger::error(string message) {
    Logger::logMessage(string("[Error] - ").append(message), RED);
  }

  void Logger::warn(string message) {
    Logger::logMessage(string("[Warn] - ").append(message), YELLOW);
  }
  
  void Logger::fatal(string message) {
    Logger::logMessage(string("[Fatal] - ").append(message), WHITE);
  }
}