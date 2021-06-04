#include "Logger.h"
using namespace std;

namespace NauLib {
  Logger::Logger() {

  }

  void Logger::logMessage(string message) {
    cout << message;
  }

  void Logger::info(string message) {
    this->logMessage(string("[Info] - ").append(message));
  }

  void Logger::error(string message) {
    this->logMessage(string("[Error] - ").append(message));
  }
}