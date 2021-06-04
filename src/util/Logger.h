#include <iostream>
using namespace std;

namespace NauLib {
  class Logger {
    private:
      void logMessage(string message);
    public:
      void info(string message);
      void warn(string message);
      void error(string message);
      void fatal(string message);
      Logger();
  };
}